#include "Arduino.h"
#include "UCSwitch.h"
#include "UCTimer.h"
UCSwitch::UCSwitch():tmr(){
  //Serial.println("Switch Created");
  _mode = 1;
  _delay = 0;
  _duration = 0;
  _finalState = 0;
  _enterLoop = 0;
  value = 0;
  tmr.init();
}

UCSwitch::UCSwitch(int Mode, int DesiredState, long Delay, long Duration, int Reset ):tmr(Delay,Duration){
  //Serial.println("Switch Created");
  _mode = Mode;
  _delay = Delay;
  _duration = Duration;
  _finalState = DesiredState;
  _enterLoop = 1;
  value=0;
  tmr.init(Delay,Duration);
}

void UCSwitch::ToggleSwitch(){
  if(value==0){
    value=1;
  }else{
    value=0;
  }
}

void UCSwitch::ToggleSwitchAfterSeconds(unsigned long Period){
  if(tmr.Pulse(Period)){
    UCSwitch::ToggleSwitch();
  }
}
void UCSwitch::OnOff(bool DesiredState){
  if(DesiredState==0){
    value=0;
  }else{
    value=1;
  }
}
int UCSwitch::VAL(){
  bool state;
  if(_mode==1){
    if(_finalState==0){
      state=0;
    }else{
      state=1;
    }
    if(_enterLoop==1){
      tmr.init(_delay,_duration);
      _enterLoop=0;
    }
    if(tmr.Value()){
      UCSwitch::OnOff(state);
    }else{
      UCSwitch::OnOff(!state);
    }
  }else{
    if(_mode==2){
      if(_enterLoop==1){
        tmr.init(_delay,_duration);
        _enterLoop=0;
      }
      if(tmr.Value()){
        UCSwitch::ToggleSwitchAfterSeconds(1000);
      }
    }else{
      if(_mode==3){
        UCSwitch::ToggleSwitch();
      }else{
        if(_mode==4){
          if(_enterLoop==1){
            tmr.init(0,5000);
            _enterLoop=0;
          }
          if(tmr.DelayElapsed(0)&&tmr.DurationElapsed(5000)){
            UCSwitch::OnOff(state);
          }else{
            UCSwitch::OnOff(!state);
          }
        }
      }
    }
  }
  return value;
}
