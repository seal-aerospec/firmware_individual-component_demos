#include "battery.h"


float batteryLevel() {
  pinMode(BAT_OUT, INPUT);
  float adcRead = analogRead(BAT_OUT);
  float espVoltage = (adcRead / 4095) * 3.3; // 4095 is 3.3V for esp32 adc
  float batVoltage = espVoltage / 0.7833; // convert to battery voltage, which uses voltage divided of ratio 0.783
  //do conversion from voltage to percentage
  float percentage = 123 - (123 / (pow(pow(batVoltage / 3.7, 80) + 1, 0.165)));
  Serial.println(percentage);
  return (int)percentage;
}
