#ifndef __PM_SENSOR_H__
#define __PM_SENSOR_H__

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PM25AQI.h>

namespace pmConsts{
  constexpr int PM_SDA {23};
  constexpr int PM_SCL {22};
  constexpr int PM_RST {A0};
  constexpr int PP5V0_EN  {13};
  constexpr int PM_I2C_FREQ {100000};
}

void setUpPMSensor();

PM25_AQI_Data pm25();

void reset();
#endif
