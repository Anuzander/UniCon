#include "UCTimer.h"
#include "Arduino.h"

UCTimer::UCTimer(){
	_delay=0;
	_duration=99999999;
	currentMillis=millis();
	previousMillis=millis();
	pulseMillis=millis();
	Multiplier=1000;
}
UCTimer::UCTimer(unsigned long Delay, unsigned long Duration){
	Multiplier=1000;
	_delay=Delay*Multiplier;
	_duration=Duration*Multiplier;
	if(Duration<=0){
		_duration=99999999;
	}else{
		_duration = _delay + _duration;
	}
	currentMillis=millis();
	previousMillis=millis();
	pulseMillis=millis();
}
void UCTimer::init(){
	currentMillis=millis();
	previousMillis=millis();
	pulseMillis=millis();
}
void UCTimer::init(unsigned long Delay, unsigned long Duration){
	Multiplier=1000;
	_delay=Delay*Multiplier;
	_duration=Duration*Multiplier;
	if(Duration<=0){
		_duration=99999999;
	}else{
		_duration = _delay + _duration;
	}
	currentMillis=millis();
	previousMillis=millis();
	pulseMillis=millis();
}
bool UCTimer::Pulse(unsigned long Period){
	if(millis()-pulseMillis>=Period*Multiplier){
		pulseMillis=millis();
		return 1;
	}else{
		return 0;
	}
}
bool UCTimer::TimeElapsed(unsigned long Period, bool ReturnValuePostPeriod){
if(Period==0){
	return 1;
}else{
	currentMillis=millis();
		if(currentMillis-previousMillis>=Period*Multiplier){
			return  ReturnValuePostPeriod;
		}else{
			return !ReturnValuePostPeriod;
		}
	}
}
bool UCTimer::DelayElapsed(unsigned long Period){
	return UCTimer::TimeElapsed(Period,1);
}
bool UCTimer::DurationElapsed(unsigned long Period){
	return UCTimer::TimeElapsed(Period,0);
}
bool UCTimer::Value(){
	if(DelayElapsed(_delay)&&DurationElapsed(_duration)){
		return 1;
	}else{
		return 0;
	}
}

