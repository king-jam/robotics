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
    DCMotor(byte pin, byte i1Pin, byte i2Pin, byte limitHigh, byte limitLow);
	~DCMotor();
    void stop_slow();
	void stop_fast();
	void setForward();
	void setReverse();
	void setSpeed(byte speed);
	void pwmAdjust(byte val);
	void setLimits(byte low, byte high);
	byte getHighLimit();
	byte getLowLimit();
	byte currentSpeed();
	bool m_isForward;
	bool m_isReverse;
  private:
	byte m_pwmPin;
	byte m_i1Pin;
	byte m_i2Pin;
 	byte m_currentSpeed;
	byte m_adjustPWM;
	byte m_calibratePWM;
	byte m_highLimit;
	byte m_lowLimit;
};

#endif

