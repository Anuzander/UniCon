#ifndef UCTimer_H
#define UCTimer_H
#include "Arduino.h"

class UCTimer{
	public:
		UCTimer();
		UCTimer(unsigned long Delay, unsigned long Duration);
		bool TimeElapsed(unsigned long Period, bool ReturnValuePostPeriod);
		bool DelayElapsed(unsigned long Period);
		bool DurationElapsed(unsigned long Period);
		bool Pulse(unsigned long Period);
		void init();
		void init(unsigned long Delay, unsigned long Duration);
	private:
		unsigned long currentMillis, previousMillis, pulseMillis, _delay, _duration;
		int Multiplier=1;


};
#endif