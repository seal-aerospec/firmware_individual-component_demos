#include "PM_Sensor.h"

TwoWire pmI2C = TwoWire(0);
Adafruit_PM25AQI pmSensor;
PM25_AQI_Data pmData;

void setUpPMSensor(){
  
  pinMode(pmConsts::PM_RST, OUTPUT);
  pinMode(pmConsts::PP5V0_EN,OUTPUT);
  digitalWrite(pmConsts::PM_RST, HIGH);
  digitalWrite(pmConsts::PP5V0_EN,HIGH);
  
  //set pins for i2c  
  pmSensor = Adafruit_PM25AQI();
  delay(1000);
  while (! pmSensor.begin_I2C()) {      // connect to the sensor over I2C
    Serial.println("Could not find PM 2.5 sensor!");
    delay(500);
  }
  Serial.println("PM2.5 sensor found!");
}

PM25_AQI_Data pm25(){
  if (!pmSensor.read(&pmData)) {
    Serial.println("Could not read from AQI");
    delay(500);  // try again in a bit!
  }
  Serial.println("AQI reading success");

  return pmData;
}

void reset() {
  digitalWrite(pmConsts::PM_RST, LOW);
  delay(10);
  digitalWrite(pmConsts::PM_RST, HIGH);
}
