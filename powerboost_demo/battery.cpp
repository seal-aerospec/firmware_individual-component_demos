#include "battery.h"


int batteryLevel() {
  pinMode(BAT_OUT, INPUT);
  float adcRead = analogRead(BAT_OUT);
  Serial.print("adcRead: ");
  Serial.println(adcRead);
  float batVoltage = adcRead*2 / 4095 * 3.3; // convert to battery voltage, which uses voltage divided of ratio 0.783
  //do conversion from voltage to percentage
  int percentage = (4.2-batVoltage)/(4.2-3.7)*100;
  Serial.println("percentage: "+String(percentage)+"%");
  return percentage;
}
