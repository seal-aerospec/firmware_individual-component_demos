#include "tmpHumiditySensor.h"

void setup(){
  Serial.begin(115200);
  setUpEnvSensor();
}

void loop(){
  Serial.print("Temp = ");
  Serial.print(readTemperature());
  Serial.println(" C");
  Serial.print("Humidity = ");
  Serial.print(readHumidity());
  Serial.println(" %");
  delay(1000);
}
