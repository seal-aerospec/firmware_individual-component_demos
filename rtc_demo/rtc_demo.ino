#include "rtc.h"

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib

void setup () {
  Serial.begin(115200);
  initRtc();
}

void loop () {
  getDateTime();
  delay(1000);
}
