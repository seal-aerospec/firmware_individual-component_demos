// Avoid powering esp32 with battery and usb at the same time
#include "sdCard.h" // requires sdCard.h and sdCard.cpp from sdCard demo folder
#include "battery.h"

SPIClass * vspi = NULL;

void setup() {
  Serial.begin(115200);
  float adcRead = batteryLevel();
  Serial.println(adcRead);
  
  // Test if SD card is inserted
  while(!sdCardInserted()) {
   delay(1000); 
  }

  // Choose chip select pin
  vspi = new SPIClass(VSPI);
  vspi->begin();
  pinMode(VSPI_SS, OUTPUT); //VSPI SS
  // initialize SD Card
  if(!SD.begin(VSPI_SS, *vspi)){
      Serial.println("Card Mount Failed");
      return;
  }
  // Check Card type
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
      Serial.println("No SD card attached");
      return;
  }

  char buf [sizeof(int)];
  sprintf (buf, "%d", adcRead);
  writeFile(SD, "/test.txt", buf);
}


void loop() {
  
}
