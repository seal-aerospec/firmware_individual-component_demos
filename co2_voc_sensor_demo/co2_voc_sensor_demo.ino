#include "co2_voc.h"

void setup() {
  Serial.begin(115200);
  Serial.println("CCS811 test");
  co2_init();
}

void loop() {
  std::pair<float, float> ccsRead = getCo2Voc();
  delay(500);
}
