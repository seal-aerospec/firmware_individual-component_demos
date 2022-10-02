// Checking battery voltage
#include "battery.h"

int adcRead = batteryLevel();
void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  Serial.println(adcRead);
}
