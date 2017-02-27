#ifndef _PCF8574_H
#define _PCF8574_H
#include "Arduino.h"

class PCF8574{
  public:
    PCF8574();
    PCF8574(uint8_t address, uint8_t sda, uint8_t slc);
    PCF8574(uint8_t deviceAddress);
    void begin();
    uint8_t read8();
    uint8_t read(uint8_t pin);
    uint8_t value();
    void write8(uint8_t value);
    void write(uint8_t pin, uint8_t value);
    void toggle(uint8_t pin);
    void shiftRight(uint8_t n=1);
    void shiftLeft(uint8_t n=1);
    int lastError();
    uint8_t getAddress();
  private:
    uint8_t _address;
    uint8_t _data;
    int _error;
};
#endif
