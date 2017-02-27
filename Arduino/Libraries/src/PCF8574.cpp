#include "PCF8574.h"
#include <Wire.h>


PCF8574::PCF8574(){
  //Serial.println("---");
  //Wire.begin(4,5);
}
PCF8574::PCF8574(uint8_t deviceAddress, uint8_t sda, uint8_t slc){
  _address = deviceAddress;
  //Wire.begin(4,5);
}

PCF8574::PCF8574(uint8_t deviceAddress){
  _address = deviceAddress;
  //Wire.begin(4,5);
}

void PCF8574::begin(){
//Serial.println(_address);
	if(_address==0){_address=getAddress();}
  Wire.begin(4,5);
}

uint8_t PCF8574::read8(){
  if (Wire.requestFrom(_address, (uint8_t)1) != 1)  {
    _error = 10;
    return _data; // last value
  }
  _data = Wire.read();
  return _data;    
}

uint8_t PCF8574::value(){
    return _data;
}

void PCF8574::write8(uint8_t value){
  //Serial.println(_address);
  _data = value;
  Wire.beginTransmission(_address);
  Wire.write(_data);
  _error = Wire.endTransmission();
}
uint8_t PCF8574::read(uint8_t pin){
  PCF8574::read8();
  return (_data & (1<<pin)) > 0;
}
void PCF8574::write(uint8_t pin, uint8_t value){
  PCF8574::read8();
  if (value == LOW)  {
    _data &= ~(1<<pin);
  }  else  {
    _data |= (1<<pin);
  }
  PCF8574::write8(_data);
}
void PCF8574::toggle(uint8_t pin){
  PCF8574::read8();
  _data ^=  (1 << pin);
  PCF8574::write8(_data);
}
void PCF8574::shiftRight(uint8_t n){
  if (n == 0 || n > 7 ) return;
  PCF8574::read8();
  _data >>= n;
  PCF8574::write8(_data);
}
void PCF8574::shiftLeft(uint8_t n){
  if (n == 0 || n > 7) return;
  PCF8574::read8();
  _data <<= n;
  PCF8574::write8(_data);
}
int PCF8574::lastError(){
  int e = _error;
  _error = 0;
  return e;
}
uint8_t PCF8574::getAddress(){
  int devicecount=0;
  Serial.println("Scanning....");
  Wire.begin(4,5);

  for (int address=1;address<127;address++){
    //Serial.print("checking address = ");
     // Serial.println(address);

    Wire.beginTransmission(address);
    _error=Wire.endTransmission();
    if(_error==0){
      Serial.print("Device Found at address 0x");
      if(address<16){
        Serial.print("0");
      }
      Serial.print(address,HEX);
        Serial.print("!           Decimal = ");
      Serial.println(address);
        devicecount++;
        _address=address;
    }else {
      if(_error==4){
        Serial.print("Unknown Error at address 0x");
        if(address<16){
          Serial.print("0");
        }
          Serial.print(address,HEX);
          Serial.println("!");
      }
    }
  }
  return _address;
}
//  return _address;

