/*
<<<<<<< HEAD
  BatteryMonitor.cpp - Library for monitoring battery voltage.
  Created by James King, February 27, 2013
  
  This class uses a voltage divider shunt on an Arduino analog
  pin to measure a battery voltage.
=======
  BatteryMonitor.h - Library for monitoring battery voltage.
  Created by James King, February 27, 2013
  Released into the public domain.
>>>>>>> Initial Battery Monitor Commit
*/

#include "BatteryMonitor.h"

<<<<<<< HEAD
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
=======
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
	R1 = 0;
	R2 = 0;
	adjustValue = 0;
}

float BatteryMonitor::read()
{
	batteryVoltage = analogRead(batteryPin);
	batteryVoltage = batteryVoltage/1023*5;
	batteryVoltage = batteryVoltgage/ratio;
	batteryVoltage = batteryVoltage + adjustValue;
	return batteryVoltage;
}

>>>>>>> Initial Battery Monitor Commit
void BatteryMonitor::calibrate(int calibrationValue)
{
	adjustValue = calibrationValue;
}

<<<<<<< HEAD
//return the last read value instead of doing a new read
float BatteryMonitor::lastValue()
{
	return batteryVoltage;
}
=======
float BatteryMonitor::lastValue()
{
	return batteryVoltage;
}
  private:
	float batteryVoltage;
    byte batteryPin;
	float ratio;
	int adjustValue;
};

>>>>>>> Initial Battery Monitor Commit
