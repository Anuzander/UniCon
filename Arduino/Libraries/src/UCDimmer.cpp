#include "Arduino.h"
#include "UCDimmer.h"
#include "UCDimmer.h"
UCDimmer::UCDimmer(SoftwareSerial *SWSER, char id):tmr(){
  swSer = SWSER;
  _id = id;
  _value = 0;
  _stepper=1;
  _stepperVal = 1;
  _loops = 1;
}
void UCDimmer::OnOff( bool DesiredState){
  swSer->write(_id);
  if(DesiredState){
    swSer->write('N');
    _value = 100;
  }else{
    swSer->write('S');
    _value=0;
  }  
  _desiredValue = _value;
}
int UCDimmer::GetCurrentValue(){
  return _value;
}
void UCDimmer::Change(int DesiredValue, int Delay, int Duration, int StepperVal, int Loops){
  int dv = 0 ;
  _desiredValue = DesiredValue;
  if(DesiredValue<_value){
    _stepper=-1;
    dv = _value-DesiredValue;
  }else{
    _stepper=1;
    dv=DesiredValue-_value;
  }//9559124444
  _loops = Loops;
  _stepperVal = StepperVal;
  if(Duration==0){
    _pulse = 1;
  }else{
    _pulse = ((Duration/dv)*_stepperVal)/_loops;
  }    
  tmr.init(Delay,Duration);
}
void UCDimmer::Change(int DesiredValue, int Delay, int Duration, int StepperVal){
  int dv = 0 ;
  _desiredValue = DesiredValue;
  if(DesiredValue<_value){
    _stepper=-1;
    dv = _value-DesiredValue;
  }else{
    _stepper=1;
    dv=DesiredValue-_value;
  }
  _loops = 1;
  _stepperVal = StepperVal;
  if(Duration==0){
    _pulse = 1;
  }else{
    _pulse = ((Duration/dv)*_stepperVal);
  }  
  tmr.init(Delay,Duration);
}
void UCDimmer::Update(String cmd){
  //DIM#XYYYZDDDDDDDDEEEEEEEEFF
  char dv[3],del[8],dur[8],lop[2];
    
  if(cmd!=""){
    if(cmd[0]=='S'){
      OnOff(0);
      return;
    }
    if(cmd[0]=='N'){
      OnOff(1);
      return;
    }
    dv[0]=cmd[1];
    dv[1]=cmd[2];
    dv[2]=cmd[3]; 
    if(cmd[5]!=0){
       _stepperVal=cmd[5];  
    }else{
      _stepperVal=1;  
    }
    for(int i=0;i<8;i++){
      del[i]=cmd[i+6];
      dur[i]=cmd[i+14];
    }
    tmr.init(atoi(del),atoi(dur));
    if(cmd.length()>21){
      lop[0]=cmd[22];
      lop[2]=cmd[23]; 
      _loops = atoi(lop); 
      Change(atoi(dv),atoi(del),atoi(dur),_stepperVal,_loops); 
    }else{
      _loops=1;
      Change(atoi(dv),atoi(del),atoi(dur),_stepperVal); 
    }
  }

  if(_value!=_desiredValue){
    if(tmr.Pulse(_pulse)){
      _value=_value+_stepper*_stepperVal;
      if(_stepper==1){
        if(_value>_desiredValue){_value=_desiredValue;}
      }else{
        if(_value<_desiredValue){_value=_desiredValue;}
      }
      swSer->write(_id);
      ConvertToDisplay(_value);
    } 
  }  
}
void UCDimmer::ConvertToDisplay(int Val){
  unsigned char dig1,dig2,dig3,dig[3];
  unsigned char x;
  unsigned char temp;
  temp=Val;
  temp=temp/10;
  dig1=Val%10;
  dig2=temp%10;
  dig3=temp/10;
  dig[0]=dig3;
  dig[1]=dig2;
  dig[2]=dig1;
  for(x=0;x<3;x++)  {
    temp=dig[x]|0x30;
    swSer->write(temp);
  }
}