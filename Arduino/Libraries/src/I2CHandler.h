#ifndef I2CHandler_H
#define I2CHandler_H
#include "UCSwitch.h"
#include "Arduino.h"
#include "PCF8574.h"


class I2CHandler{
  public:
    I2CHandler();
    I2CHandler(uint8_t address, uint8_t sda, uint8_t slc);
    void init();
    void Update(String Command);
    int getResult();
    uint8_t GetStatus();
    void WriteValue(uint8_t value);
  private:
    PCF8574 ic;
    UCSwitch P0,P1,P2,P3,P4,P5,P6,P7;
    uint8_t m_address=0;
    uint8_t _sda = 4;
    uint8_t _slc = 5;
    int value;

    char digitPin[3];
    int dp = 0;
    char state[3];
    char Mode[3];
    String timeDelay, timeDuration;
    char Delay[8],Duration[8];
    unsigned long dur=0,del=0;
    int j=0;
    int iState=0, iMode=0;
    int _pin[3];
	
    String result;

    friend class PCF8574;
    friend class UCSwitch;
};
#endif

