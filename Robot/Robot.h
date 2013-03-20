/*
  Robot.h - Library for controlling EECE4630 Wall Follower.
  Created by James King, Steve MacKinnon, and Sean Zensen March 19, 2013
*/

#ifndef Robot_h
#define Robot_h

#include "WProgram.h"
#include <DCMotor.h>
#include <Ping.h>
#include <BatteryMonitor.h>

#define R_MOTOR_PWM 14
#define R_MOTOR_I1 12
#define R_MOTOR_I2 13
#define L_MOTOR_PWM 15
#define L_MOTOR_I1 17
#define L_MOTOR_I2 16
#define F_PING 1
#define RF_PING 2
#define RB_PING 3
#define BAT_MON 4

class Robot
{
  public:
    Robot();
	~Robot();
	DCMotor m_rightMotor;
	DCMotor m_leftMotor;
	Ping m_frontPing;
	Ping m_rightFrontPing;
	Ping m_rightBackPing;
	BatteryMonitor m_batteryMonitor;
  private:
};

#endif

