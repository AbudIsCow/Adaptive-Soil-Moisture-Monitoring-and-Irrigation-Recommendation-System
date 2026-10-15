#include <SD.h>
#include "RTClib.h"
RTC_DS3231 rtc;
const int SOIL_MOISTURE_PIN = 34;
const int SD_CS_PIN = 5;
int fail = 0;

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
    dataFile.println("timestamp,millis,s1,s2,s3,s4,s5,soil_adc");
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

}