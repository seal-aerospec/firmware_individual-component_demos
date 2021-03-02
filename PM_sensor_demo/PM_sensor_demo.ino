#include "PM_Sensor.h"
void setup() {
  Serial.begin(9600);
  delay(1000);
  setUpPMSensor();
}

void loop() {
  delay(1000);
  Serial.println(pm25());
}
