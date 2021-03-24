#ifndef BAT_H
#define BAT_H
#include <Arduino.h>
#include <math.h>
#define BAT_OUT 34
#define CHARGE 36 //VP
#define VSPI_SS  13

// TODO map adc value to percentage
float batteryLevel();

#endif
