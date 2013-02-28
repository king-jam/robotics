/*
  BatteryMonitor.cpp - Library for monitoring battery voltage.
  Created by James King, February 27, 2013
  
  This class uses a voltage divider shunt on an Arduino analog
  pin to measure a battery voltage.
*/

#include "BatteryMonitor.h"

//constructor function
BatteryMonitor::BatteryMonitor(byte pin, float r1, float r2)
{
	pinMode(pin,INPUT); //set analog pin as input
	batteryPin = pin; //set pin to batteryPin for later use
	batteryVoltage = 0; //initialize variable as 0
	ratio = r2/(r1+r2); //calculate the resistor divider ratio
	adjustValue = 0; //calibration value to adjust measured voltage
}

//destructor function, probably not necessary
BatteryMonitor::~BatteryMonitor()
{
	//set all private variables to 0
	batteryVoltage = 0;
	ratio = 0;
	adjustValue = 0;
}

//read battery voltage
float BatteryMonitor::read()
{
	//read the raw 10-bit value
	batteryVoltage = analogRead(batteryPin);
	//convert raw value to voltage
	batteryVoltage = batteryVoltage/1023*5;
	//divide by resistor ratio to get actual voltage
	batteryVoltage = batteryVoltage/ratio;
	//add adjust value if needed, calibration bit
	batteryVoltage = batteryVoltage + adjustValue;
	//return value
	return batteryVoltage;
}

//set calibration values
void BatteryMonitor::calibrate(int calibrationValue)
{
	adjustValue = calibrationValue;
}

//return the last read value instead of doing a new read
float BatteryMonitor::lastValue()
{
	return batteryVoltage;
}