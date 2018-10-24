#include <stdint.h>
#include <SPI.h>

const uint8_t chipSelectPin = 10;
const uint8_t RDSR = 0x05;
const uint8_t READ = 0x03;
uint8_t readAddr = 0x0000;
uint8_t outputByte = 0;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT);
  
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE3));
  delay(10);

  digitalWrite(chipSelectPin,LOW);
  SPI.transfer(READ);
  SPI.transfer16(readAddr);
  for(uint16_t i=0;i<32000;++i){
    outputByte = SPI.transfer(0x00);
    Serial.write(outputByte);
  }
  
  digitalWrite(chipSelectPin, HIGH);
  SPI.endTransaction();

  
}

void loop() {
}
