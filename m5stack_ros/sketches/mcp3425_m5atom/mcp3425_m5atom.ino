#include <Wire.h>
#define MCP3425_address 0x68
#define configRegister 0b10011000 //16bit 15sps PGA x1 

void setup() {
  Serial.begin(9600);
  //Wire.begin(25, 21);
  Wire.begin(26, 32);
  Wire.beginTransmission(MCP3425_address);
  Wire.write(configRegister);
  Wire.endTransmission();
}

void loop() {
  float vol = (int16_t)readADC() * 2.048 / 32767.0 ;
  if (fabs(vol) > 3.3) {
     vol = 0;
  }
  Serial.println(String(vol,5));
  delay(100);
}

float readADC() {
  Wire.requestFrom(MCP3425_address, 2);
  return ( (Wire.read() << 8 ) + Wire.read() );
}
