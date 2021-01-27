#include "tmpHumiditySensor.h"

TwoWire tmpHumI2C = TwoWire(0);
Adafruit_SHT31 sht31;

void setUpEnvSensor(){
  pinMode(consts::TMP_HUM_RST, OUTPUT);
  digitalWrite(consts::TMP_HUM_RST, HIGH);
  digitalWrite(consts::TMP_HUM_RST, HIGH);
  pinMode(consts::TMP_HUM_ALR, INPUT);
  //set pins for i2c
  tmpHumI2C.begin(consts::TMP_HUM_SDA, consts::TMP_HUM_SCL, consts::TMP_HUM_I2C_FREQ);

  sht31 = Adafruit_SHT31(&tmpHumI2C);
  sht31.begin(0x44); //0x44 is default mem address for env sensor, 0x45 can alternatively be used
}

float readTemperature(void) {
  return sht31.readTemperature();
}

float readHumidity(void) {
  return sht31.readHumidity();
}

void altAdr() {
  pinMode(consts::TMP_HUM_ADR, OUTPUT);
  digitalWrite(consts::TMP_HUM_ADR, HIGH);
}

void hardwareRst() {
  digitalWrite(consts::TMP_HUM_RST, LOW);
  delay(10);
  digitalWrite(consts::TMP_HUM_RST, HIGH);
}
