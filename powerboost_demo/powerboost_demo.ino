// Checking battery voltage
#include "battery.h"


void setup() {
  Serial.begin(115200);
  int adcRead = batteryLevel();
  Serial.println(adcRead);
}

void loop() {
  
}
