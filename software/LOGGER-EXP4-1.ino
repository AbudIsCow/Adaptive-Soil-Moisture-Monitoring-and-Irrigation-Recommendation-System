#include <SD.h>
#include "RTClib.h"
RTC_DS3231 rtc;
const int SOIL_MOISTURE_PIN_1 = 34;
const int SOIL_MOISTURE_PIN_2 = 32;
const int SOIL_MOISTURE_PIN_3 = 33;
const int SOIL_MOISTURE_PIN_4 = 35;
const int SOIL_MOISTURE_PIN_5 = 36;
const int SD_CS_PIN = 5;

void setup() {
  Serial.begin(115200);
  delay(5000);
  if (!SD.begin(SD_CS_PIN)) {
    while (true) {
      Serial.println("Mount has failed.");
      delay(1000);
    }
  }
  if (!rtc.begin()) {
    while (true) {
      Serial.println("Couldn't find RTC module.");
      delay(1000);
    }
  }
  if (!SD.exists("/exp4-1.csv")) {
    File dataFile = SD.open("/exp4-1.csv", FILE_WRITE);
    if (!dataFile) {
      while (true) {
        Serial.println("Writing header has failed.");
        delay(1000);
      }
    }
    dataFile.println("timestamp,millis,s1,s2,s3,s4,s5,temp_c");
    dataFile.close();
  }
  DateTime now = rtc.now();
  if ((now.year()) < 2026) {
    while (true) {
      Serial.println("RTC Module has lost power.");
      delay(1000);
    }
  }
}

void loop() {
  delay(5000);
  unsigned long ms = millis();
  unsigned long s1 = analogRead(SOIL_MOISTURE_PIN_1);
  unsigned long s2 = analogRead(SOIL_MOISTURE_PIN_2);
  unsigned long s3 = analogRead(SOIL_MOISTURE_PIN_3);
  unsigned long s4 = analogRead(SOIL_MOISTURE_PIN_4);
  unsigned long s5 = analogRead(SOIL_MOISTURE_PIN_5);
  DateTime now = rtc.now();
  float temp_c = rtc.getTemperature();
  char timeStamp[20];
  sprintf(timeStamp, "%04u-%02u-%02u %02u:%02u:%02u", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  File dataFile = SD.open("/exp4-1.csv", FILE_APPEND);
  if (!dataFile) {
    Serial.println("...");
    return;
  }
  dataFile.print(timeStamp);
  dataFile.print(",");
  dataFile.print(ms);
  dataFile.print(",");
  dataFile.print(s1);
  dataFile.print(",");
  dataFile.print(s2);
  dataFile.print(",");
  dataFile.print(s3);
  dataFile.print(",");
  dataFile.print(s4);
  dataFile.print(",");
  dataFile.print(s5);
  dataFile.print(",");
  dataFile.println(temp_c, 2);
  dataFile.close();

  Serial.print(timeStamp);
  Serial.print(",");
  Serial.print(ms);
  Serial.print(",");
  Serial.print(s1);
  Serial.print(",");
  Serial.print(s2);
  Serial.print(",");
  Serial.print(s3);
  Serial.print(",");
  Serial.print(s4);
  Serial.print(",");
  Serial.print(s5);
  Serial.print(",");
  Serial.println(temp_c, 2);
}