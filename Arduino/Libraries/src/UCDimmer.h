#ifndef UCDimmer_H
#define UCDimmer_H
#include "UCTimer.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

class UCDimmer{
  public:
    UCDimmer(SoftwareSerial *SWSER, char id);
    void OnOff ( bool DesiredState);
    int GetCurrentValue();
    void Change (int DesiredValue, int Delay, int Duration, int StepperVal, int Loops);
    void Change (int DesiredValue, int Delay, int Duration, int StepperVal);
    void Update(String cmd);
  private:
    void ConvertToDisplay(int Val);
    UCTimer tmr;
    SoftwareSerial *swSer;
    unsigned long currentMillis; 
    unsigned long previousMillis; 
    unsigned long _pulse;
    int _rx,_tx,_stepper,_stepperVal,_value,_desiredValue,_loops;
    char _id;
  friend class UCTimer;
};
#endif

