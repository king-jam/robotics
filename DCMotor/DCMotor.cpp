/*
  DCMotor.cpp - Library for controlling 7.2V DC Motor.
  Created by James King, February 27, 2013
*/

#include "DCMotor.h"

//constructor	-  PWM Pin - H-Bridge I1 - H-Bridge I2 - Wheel Radius - Low PWM Limit - High PWM Limit
DCMotor::DCMotor(byte pin, byte i1Pin, byte i2Pin, byte wheelRadius, byte limitLow, byte limitHigh)
{
	pinMode(pin,OUTPUT);
	pwmPin = pin;
	wheelRadius = wheelRadius;
	highLimit = limitHigh;
	lowLimit = limitLow;
 	currentSpeed = 0;
	currentPWM = 0;
	calibratePWM = 0;
	adjustPWM = 0;
}

//destructor, probably not needed
DCMotor::~DCMotor()
{
 	currentSpeed = 0;
	currentPWM = 0;
	adjustPWM = 0;
	calibratePWM = 0;
	wheelRadius = 0;
	lowLimit = 0;
	highLimit = 0;
}

void DCMotor::stop_slow()
{
	//stuff
}

void DCMotor::stop_fast()
{
	//stuff
}

void DCMotor::coast()
{
	//stuff
}

void DCMotor::forward(byte speed)
{
	//stuff
}

void DCMotor::back(byte speed)
{
	//stuff
}

void DCMotor::forwardX(byte dist)
{
	//stuff
}

void DCMotor::backX(byte dist)
{
	//stuff
}

void DCMotor::pwmAdjust(byte val)
{
	//stuff
}

void DCMotor::setLimits(byte low, byte high)
{
	lowLimit = low;
	highLimit = high;
}

byte DCMotor::currentSpeed()
{
	//stuff
}