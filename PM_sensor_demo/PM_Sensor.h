#ifndef __PM_SENSOR_H__
#define __PM_SENSOR_H__

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PM25AQI.h>

namespace pmConsts{
  constexpr int PM_SDA {19};
  constexpr int PM_SCL {18};
  constexpr int PM_I2C_FREQ {100000};
}

void setUpPMSensor();

uint16_t pm25();

#endif
