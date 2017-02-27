#ifndef Structure_h
#define Structure_h
#include "Arduino.h"

typedef struct{
  String _Mode;
  String _Ssid;
  String _Pwd;
  String _APIP;
  String _STIP;  
}WifiConfig;

typedef struct{
  int _Delay;
  int _Duration;  
}TimerConfig;

typedef struct{
  int _Mode;
  int _DesiredState;
  TimerConfig _Tmr;
  int _Reset; 
}SwitchConfig;


typedef struct{
  int _DesiredValue;
  TimerConfig _Tmr;
  int _StepperVal;
  int _Loop;
}DimmerConfig;

typedef struct{
  String _Source;
  String _ChipId;
  String _Password;
  String _Input;
}InputValues;

typedef struct{
  int _Address;
  int _SDA;
  int _SLC;
}IOConfig;

typedef struct{
  int _Year;
  int _Month;
  int _Day;
  int _Hour;
  int _Minute;
  int _Second;
}DateTime;

typedef struct{
  int _Switches;
  int _Dimmers;
  int _KeyPad;
  int _IO;
  String _Password;
  String _ChipId;
}DeviceConfig;


#endif
