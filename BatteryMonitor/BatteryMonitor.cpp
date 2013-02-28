/*
  BatteryMonitor.h - Library for monitoring battery voltage.
  Created by James King, February 27, 2013
  Released into the public domain.
*/

#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor(byte pin, float r1, float r2)
{
	pinMode(pin,INPUT);
	batteryPin = pin;
	batteryVoltage = 0;
	ratio = r2/(r1+r2);
	adjustValue = 0;
	
}

BatteryMonitor::~BatteryMonitor()
{
	batteryVoltage = 0;
	ratio = 0;
	adjustValue = 0;
}

float BatteryMonitor::read()
{
	batteryVoltage = analogRead(batteryPin);
	batteryVoltage = batteryVoltage/1023*5;
	batteryVoltage = batteryVoltage/ratio;
	batteryVoltage = batteryVoltage + adjustValue;
	return batteryVoltage;
}

void BatteryMonitor::calibrate(int calibrationValue)
{
	adjustValue = calibrationValue;
}

float BatteryMonitor::lastValue()
{
	return batteryVoltage;
}