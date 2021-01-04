/*
  Read NMEA sentences over I2C using Ublox module SAM-M8Q

  This example reads the NMEA characters over I2C and pipes them to MicroNMEA
  This example will output your current long/lat and satellites in view

  For MicroNMEA info see https://github.com/stevemarple/MicroNMEA
*/

#include "gpsSensor.h"

SFE_UBLOX_GPS myGPS;
char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

bool setUpGpsSensor() {
  Wire.begin();
  Serial.println("Initializing GPS");
  if (myGPS.begin(Wire, 0x42) == false)  //0x42 is default address
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    return false;
  }
  else 
  {
    Serial.println("GPS detected");
    return true;
  }
}

bool processIncomingData() {
  return myGPS.checkUblox();
}

bool gpsDataValid() {
  if(nmea.isValid())
  {
    return true;
  }
  else
  {
    Serial.print("No Fix - ");
    Serial.print("Num. satellites: ");
    Serial.println(nmea.getNumSatellites());
    return false;
  }
}

double getLatitude() {
  long latitude_mdeg = nmea.getLatitude();
  double latitude = latitude_mdeg / 1000000.;  // convert nmea data
  return latitude;
}

double getLongitude() {
  long longitude_mdeg = nmea.getLongitude();
  double longitude = longitude_mdeg / 1000000.;  // convert nmea data
  return longitude;
}

//This function gets called from the SparkFun Ublox Arduino Library, checkUblox()
//As each NMEA character comes in you can specify what to do with it
//Useful for passing to other libraries like tinyGPS, MicroNMEA, or even
//a buffer, radio, etc.
void SFE_UBLOX_GPS::processNMEA(char incoming)
{
  //Take the incoming char from the Ublox I2C port and pass it on to the MicroNMEA lib
  //for sentence cracking
  nmea.process(incoming);
}
