#include <SD.h>
const int SOIL_MOISTURE_PIN = 34;
const int SD_CS_PIN = 5;
int count = 1;
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
  if (!SD.exists("/test.csv")) {
    File dataFile = SD.open("/test.csv", FILE_WRITE);
    if (!dataFile)) {
      while (true) {
        Serial.println("Writing header has failed.");
        delay(1000);
    }
  }
    dataFile.println("count,millis,soil_adc");
    dataFile.close();
  }
}

void loop() {
  if (Serial.available() > 0) {
    Serial.read();
    while (true) {
      delay(1000);
    }
  }
  unsigned long timeStamp = millis();
  unsigned long soil_ADC = analogRead(SOIL_MOISTURE_PIN);

  File dataFile = SD.open("/test.csv", FILE_APPEND);
  if (!dataFile) {
    fail = 1;
  }
  if (fail == 0) {
    dataFile.print(count);
    dataFile.print(",");
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.println(soil_ADC);
    Serial.print(count);
    Serial.print(",");
    Serial.print(timeStamp);
    Serial.print(",");
    Serial.println(soil_ADC);
  }
  if (fail == 1) {
      Serial.println("FAILED");
      fail = 0;
  }
  dataFile.close();
  count = count + 1;
  delay(5000);
}
