/*
  DCMotor.h - Library for controlling 7.2V DC Motor.
  Created by James King, February 27, 2013
*/

#ifndef DCMotor_h
#define DCMotor_h

#include "WProgram.h"

class DCMotor
{
  public:
    DCMotor(byte pin, byte i1Pin, byte i2Pin, byte wheelRadius, byte limitHigh, byte limitLow);
	~DCMotor();
    void stop_slow();
	void stop_fast();
	void coast();
	void forward(byte speed);
	void back(byte speed);
	void forwardX(byte dist);
	void backX(byte dist);
	void pwmAdjust(byte val);
	void setLimits(byte low, byte high);
	byte currentSpeed();
  private:
	byte pwmPin;
 	byte currentSpeed;
	byte currentPWM;
	byte adjustPWM;
	byte calibratePWM;
	byte wheelRadius;
	byte highLimit;
	byte lowLimit;
};

#endif

