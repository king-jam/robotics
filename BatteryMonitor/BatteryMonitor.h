/*
  BatteryMonitor.h - Library for monitoring battery voltage.
  Created by James King, February 27, 2013
  
  This class uses a voltage divider shunt on an Arduino analog
  pin to measure a battery voltage.
*/

#ifndef BatteryMonitor_h
#define BatteryMonitor_h

#include "WProgram.h"

class BatteryMonitor
{
  public:
    BatteryMonitor(byte pin, float r1, float r2);
	~BatteryMonitor();
    float read();
    void calibrate(int adjustValue);
	float lastValue();
  private:
 	float batteryVoltage;
    byte batteryPin;
	float ratio;
	int adjustValue;
};

#endif

