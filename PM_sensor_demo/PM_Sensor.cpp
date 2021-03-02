#include "PM_Sensor.h"

TwoWire pmI2C = TwoWire(0);
Adafruit_PM25AQI pmSensor;
PM25_AQI_Data pmData;

void setUpPMSensor(){
  
  pinMode(pmConsts::PM_RST, OUTPUT);
  //pinMode(pmConsts::PM_SET, INPUT);
  digitalWrite(pmConsts::PM_RST, HIGH);
  
  //set pins for i2c
  pmI2C.begin(pmConsts::PM_SDA, pmConsts::PM_SCL, pmConsts::PM_I2C_FREQ);
  pmSensor = Adafruit_PM25AQI();
  delay(1000);
  if (! pmSensor.begin_I2C(&pmI2C)) {      // connect to the sensor over I2C
    Serial.println("Could not find PM 2.5 sensor!");
    while (1) delay(10);
  }
}

PM25_AQI_Data pm25(){
  if (!pmSensor.read(&pmData)) {
    Serial.println("Could not read from AQI");
    delay(500);  // try again in a bit!
  }
  Serial.println("AQI reading success");

  return pmData;
}
