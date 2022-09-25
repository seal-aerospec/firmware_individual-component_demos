
/* EINK display demo for Aerospec
 * Avoid refrshing display more than once every 3 minutes
 * 
 */
 
#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_EPD.h"

// SCK -> 5
// MISO -> 19
// MOSI -> 18
#define SD_CS 14 
#define SRAM_CS 32 
#define EPD_CS 15
#define EPD_DC 33
#define EPD_RESET -1 // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1  // can set to -1 to not use a pin (will wait a fixed delay)
#define EPD_ENA     27 // set low to turn off display

#define FLEXIBLE_213
#define COLOR1 EPD_BLACK
#define COLOR2 EPD_RED

void displayPower(bool enable) {
  if(enable) {
    digitalWrite(EPD_ENA, HIGH);
    Serial.println("Powering on Display");
  }
  else {
    digitalWrite(EPD_ENA, LOW);
    Serial.println("Powering off Display");
  }
}

void resetEInk() {
  digitalWrite(EPD_RESET, HIGH);
  digitalWrite(EPD_RESET, LOW);
}

bool isBusy() {
  bool busy =  digitalRead(EPD_BUSY) == LOW;
  if(busy) {
    Serial.println("Busy");
  }
  return busy;
}

void setup(void) {
  Serial.begin(115200);
  Serial.print("Hello! EPD Test");

  pinMode(EPD_BUSY, INPUT);
  pinMode(EPD_RESET, OUTPUT);
  digitalWrite(EPD_RESET, LOW);
  pinMode(EPD_ENA, OUTPUT);
  displayPower(true);
  // Init 2.13" 212x104 Eink display
  /* Uncomment the following line if you are using 2.13" tricolor EPD */
  //Adafruit_IL0373 display(212, 104, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

  /* Uncomment the following line if you are using 2.13" monochrome 250*122 EPD */  
  Adafruit_SSD1675 display(250, 122, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
  /*As of April 27, 2020 Adafruit is selling a version with SSD1680 chipset*/
  //Adafruit_SSD1680 display(250, 122, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
  delay(500);
  display.begin();
  Serial.println("Initialized");
  display.setRotation(4);
  
  // large block of text
  display.clearBuffer();
  display.setCursor(10, 10);
  display.setTextSize(1);
  display.setTextColor(EPD_BLACK);
  display.setTextWrap(true);
  display.print("Is this working? I sure hope so.");
  display.display();
  displayPower(false);
}

void loop() {
  //delay(500);
}
