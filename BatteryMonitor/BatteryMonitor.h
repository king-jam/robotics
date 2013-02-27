/*
  BatteryMonitor.h - Library for monitoring battery voltage.
  Created by James King, February 27, 2013
<<<<<<< HEAD
  
  This class uses a voltage divider shunt on an Arduino analog
  pin to measure a battery voltage.
=======
  Released into the public domain.
>>>>>>> Initial Battery Monitor Commit
*/

#ifndef BatteryMonitor_h
#define BatteryMonitor_h

#include "WProgram.h"

<<<<<<< HEAD
class BatteryMonitor
=======
class BatterMonitor
>>>>>>> Initial Battery Monitor Commit
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

