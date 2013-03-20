/*
  DCMotor.cpp - Library for controlling 7.2V DC Motor.
  Created by James King, February 27, 2013
*/

#include "DCMotor.h"

//constructor	- PWM Pin - H-Bridge I1 - H-Bridge I2 - Low PWM Limit - High PWM Limit
DCMotor::DCMotor(byte pin, byte i1Pin, byte i2Pin, byte limitLow, byte limitHigh)
{
	pinMode(pin,OUTPUT);
	pinMode(i1Pin,OUTPUT);
	pinMode(i2Pin,OUTPUT);
	m_pwmPin = pin;
	m_i1Pin = i1Pin;
	m_i2Pin = i2Pin;
	m_highLimit = limitHigh;
	m_lowLimit = limitLow;
 	m_currentSpeed = 0;
	m_calibratePWM = 0;
	m_adjustPWM = 0;
	m_isForward = 0;
	m_isReverse = 0;
}

//destructor, probably not needed
DCMotor::~DCMotor()
{
 	m_currentSpeed = 0;
	m_adjustPWM = 0;
	m_calibratePWM = 0;
	m_lowLimit = 0;
	m_highLimit = 0;
	m_isForward = 0;
	m_isReverse = 0;
}

void DCMotor::stop_slow()
{
	analogWrite(m_pwmPin, 0);
}

void DCMotor::stop_fast()
{
	analogWrite(m_pwmPin,0);
	digitalWrite(m_i1Pin,HIGH);
	digitalWrite(m_i2Pin,HIGH);
}

void DCMotor::setSpeed(byte speed){
	byte value;
	value = map(speed, 0, 100, m_lowLimit, m_highLimit);
	value = value + m_adjustPWM + m_calibratePWM;
	m_currentSpeed = value;
	analogWrite(m_pwmPin, value);
}

void DCMotor::setForward(){
	digitalWrite(m_i1Pin,LOW);
	digitalWrite(m_i2Pin,HIGH);
	m_isForward = 1;
	m_isReverse = 0;
}

void DCMotor::setReverse(){
	digitalWrite(m_i1Pin,HIGH);
	digitalWrite(m_i2Pin,LOW);
	m_isReverse = 1;
	m_isForward = 0;
}

void DCMotor::pwmAdjust(byte value)
{
	m_adjustPWM = value;
}

void DCMotor::setLimits(byte low, byte high)
{
	m_lowLimit = low;
	m_highLimit = high;
}

byte DCMotor::getHighLimit(){
	return m_highLimit;
}

byte DCMotor::getLowLimit(){
	return m_lowLimit;
}

byte DCMotor::currentSpeed()
{
	return m_currentSpeed;
}