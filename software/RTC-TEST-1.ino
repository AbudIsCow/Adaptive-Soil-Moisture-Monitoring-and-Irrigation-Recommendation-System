#include "RTClib.h"
RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);
  delay(5000);
  if (!rtc.begin()) {
    while (true) {
      Serial.println("Couldn't find RTC module.");
      delay(1000);
    }
  }

}

void loop() {
  DateTime now = rtc.now();
  Serial.print("Current Date & Time (YYYY/MM/DD), (HH:MM:SS): (");
  Serial.print(now.year());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.print(now.day());
  Serial.print("), (");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.println(")");
  delay(1000);
}