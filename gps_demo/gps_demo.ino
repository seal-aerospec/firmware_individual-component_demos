#include "gpsSensor.h"

void setup()
{
  Serial.begin(115200);
  setUpGpsSensor();
}

void loop()
{
  processIncomingData(); //See if new data is available. Process bytes as they come in.

  if(gpsDataValid())
  {
    long latitude = getLatitude();
    long longitude = getLongitude();
    Serial.print("Latitude (deg): ");
    Serial.println(latitude, 6);  
    Serial.print("Longitude (deg): ");
    Serial.println(longitude, 6);  
  }
  delay(250); //Don't pound too hard on the I2C bus
}
