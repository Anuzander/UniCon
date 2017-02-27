#include "I2CHandler.h"
#include "PCF8574.h"
#include "UCSwitch.h"


I2CHandler::I2CHandler():ic(63),P0(),P1(),P2(),P3(),P4(),P5(),P6(),P7(){
	delay(10);
//ic.begin();
}
I2CHandler::I2CHandler(uint8_t address, uint8_t sda, uint8_t slc):ic(63),P0(),P1(),P2(),P3(),P4(),P5(),P6(),P7(){
	delay(10);
	m_address=address;
     ic=PCF8574(m_address);

	_sda=sda;
	_slc=slc;
	//ic.begin();
}
//8953610383
void I2CHandler::init(){
  if(m_address==0){
    m_address=ic.getAddress();
ic=PCF8574(m_address);
  }

    //Serial.println(m_address);

	ic.begin();
}
uint8_t I2CHandler::GetStatus(){
	
	return ic.read8();
}
int I2CHandler::getResult(){
	ic.begin();
  for(int i=0;i<=16;i++){
    ic.write8(i);
    delay(500);
    Serial.println(i);
  }
  

}
void I2CHandler::WriteValue(uint8_t val){
	ic.write8(val);
}
void I2CHandler::Update(String Command){
  /*Command String format AABCDDDDDDDDEEEEEEEE eg 01110000000000000060
   * AA=PORT/PIN NUMBER eg 01,21,AA
   * B =On/Off eg 1=Off/0=On 
   * C =Mode 1=latching 2=Momentary 3=toggle 4=door
   * DDDDDDDD = Delay Period In Seconds eg 00000000 = no delay, 00000060 delay of 60 seconds
   * EEEEEEEE = Duration Period in Seconds eg 00000000 = on/off untill next command, 00000060 on/off for 60 seconds and then change state to off/on
   */
  result=Command;
  while (Command!=""){
    String readInput = Command;
    Command ="";
    Serial.println(readInput);
    digitPin[0] = readInput[0];
    digitPin[1] = readInput[1];
    if(readInput.substring(0,2)=="AA"||readInput.substring(0,2)=="aa"){
      dp=20;
    }else{
      dp= atoi(digitPin);
    }
    Serial.println(dp);
    state[0] = readInput[2];
    Mode[0] = readInput[3];
    iState = atoi(state);
    iMode = atoi(Mode);
    timeDelay = readInput.substring(5,12);
    timeDuration = readInput.substring(13,20);
    for(j=0;j<8;j++){
      Delay[j]=timeDelay[j];
      Duration[j]=timeDuration[j];
    }
    del = atoi(Delay);
    dur = atoi(Duration);
    /*
     * P0=8
     * P1=7
     * P2=6
     * P3=5
     * P4=1
     * P5=2
     * P6=3
     * P7=4
     * pin = pin - 20
     * ONOFFVAL = P0.VAL*2^7+P1.VAL*2^6+P2.VAL*2^5+P3.VAL*2^4+P7.VAL*2^3+P6.VAL*2^2+P5.VAL*2+P4.VAL
     
	Serial.print("Mode = ");
	Serial.println(iMode);
	Serial.print("State = ");
	   Serial.println(iState);
	Serial.print("Del = ");
	   Serial.println(del);
	Serial.print("Dur = ");
	   Serial.println(dur);
	Serial.print("Pin = ");
	   Serial.println(dp);*/
    switch(dp){
      case 21:
        P4=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 22:
        P5=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 23:
        P6=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 24:
        P7=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 25:
        P3=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 26:
        P2=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 27:
        P1=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 28:
        P0=UCSwitch( iMode,iState,del, dur,0);
        break;
      case 20:
        P0=UCSwitch( iMode,iState,del, dur,0);
        P1=UCSwitch( iMode,iState,del, dur,0);
        P2=UCSwitch( iMode,iState,del, dur,0);
        P3=UCSwitch( iMode,iState,del, dur,0);
        P4=UCSwitch( iMode,iState,del, dur,0);
        P5=UCSwitch( iMode,iState,del, dur,0);
        P6=UCSwitch( iMode,iState,del, dur,0);
        P7=UCSwitch( iMode,iState,del, dur,0);
        break;
    }
  }
  value=P0.VAL()+P1.VAL()*2+P2.VAL()*4+P3.VAL()*8+P4.VAL()*16+P5.VAL()*32+P6.VAL()*64+P7.VAL()*128;
//Serial.print("VALUE = = = = = = = ");
	   //Serial.println(value);

  ic.write8(value);
}

