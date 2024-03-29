#include "sdCard.h"

SPIClass * vspi = NULL;

void setup(){
    Serial.begin(115200);

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
    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }
    // Print card capcacity
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    //listDir(SD, "/", 0);
    //createDir(SD, "/mydir");
    //listDir(SD, "/", 0);
    //removeDir(SD, "/mydir");
    //listDir(SD, "/", 2);
    // if(SD.exists("/hello.txt")) {
    //   Serial.println("hello file exists");
      writeFile(SD, "/hello.txt", "Hello ");
      appendFile(SD, "/hello.txt", "World!\n");
      appendFile(SD, "/hello.txt", "DEF ");
      readFile(SD, "/hello.txt");
    //}
    // else {
    //   Serial.println("hello file doesn't exist");
    // }
    //deleteFile(SD, "/foo.txt");
    //renameFile(SD, "/hello.txt", "/foo.txt");
    //readFile(SD, "/foo.txt");
    //testFileIO(SD, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void loop(){

}
