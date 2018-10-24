#include <Wire.h>
#include <stdint.h>

#define AT24C02_ADDR 0x50

void setup() {
  uint8_t dataAddr;
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(31000L);
  Wire.beginTransmission(AT24C02_ADDR);
  Wire.write(0x00); //Sets the start address for use in the upcoming reads
  Wire.endTransmission();
  for(uint8_t i=0;i<8;++i){ //cycle through enough times to capture entire EEPROM
    Wire.requestFrom(AT24C02_ADDR,32,1); //read 32 bytes at a time
    while (Wire.available()){
      uint8_t c = Wire.read();
      Serial.write(c); //Send raw data over serial to computer
    }
  }

}

void loop() {
  
}
