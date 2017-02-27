#ifndef UCSwitch_H
#define UCSwitch_H
#include "UCTimer.h"
#include "Arduino.h"


class UCSwitch{
  public:
    UCSwitch();
    UCSwitch(int Mode, int DesiredState, long Delay, long Duration, int Reset );
    void OnOff(bool DesiredState);
    void ToggleSwitch();
    void ToggleSwitchAfterSeconds(unsigned long Period);
    int VAL();
  private:
    UCTimer tmr;
    int value;
    int _mode;
    long _delay;
    long _duration;
    int _presentState;
    int _finalState;
    unsigned long currentMillis; 
    unsigned long previousMillis; 
    unsigned long ToggleMillis;  
    int _enterLoop=0;

    friend class UCTimer;
  
};
#endif
