#include "PM_Sensor.h"

TwoWire pmI2C = TwoWire(0);
Adafruit_PM25AQI pmSensor;
PM25_AQI_Data pmData;

void setUpPMSensor(){

  //set pins for i2c
  pmI2C.begin(pmConsts::PM_SDA, pmConsts::PM_SCL, pmConsts::PM_I2C_FREQ);

  pmSensor = Adafruit_PM25AQI();
  delay(1000);
  Serial.println(pmSensor.begin_I2C());//&pmI2C));
}

uint16_t pm25(){
  if(!pmSensor.read(&pmData)){
    return 7;
  }

  return pmData.pm25_standard;
}
