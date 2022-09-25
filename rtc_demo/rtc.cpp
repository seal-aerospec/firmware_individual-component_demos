#include "rtc.h"

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

bool initRtc() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
    return false;
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  return true;
}

DateTime getDateTime() {
  DateTime current = rtc.now();

  Serial.print(current.year(), DEC);
  Serial.print('/');
  Serial.print(current.month(), DEC);
  Serial.print('/');
  Serial.print(current.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[current.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(current.hour(), DEC);
  Serial.print(':');
  Serial.print(current.minute(), DEC);
  Serial.print(':');
  Serial.print(current.second(), DEC);
  Serial.println();

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(current.unixtime());
  Serial.print("s = ");
  Serial.print(current.unixtime() / 86400L);
  Serial.println("d");

  // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
  DateTime future (current + TimeSpan(7,12,30,6));

  Serial.print(" now + 7d + 12h + 30m + 6s: ");
  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(' ');
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();

  Serial.print("Temperature: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");

  Serial.println();
  return current;
}
