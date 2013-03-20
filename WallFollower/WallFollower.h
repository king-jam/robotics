/*
  WallFollower.h - Library for controlling EECE4630 Wall Follower.
  Created by James King, Steve MacKinnon, and Sean Zensen March 19, 2013
*/

#ifndef WallFollower_h
#define WallFollower_h

#include "WProgram.h"
#include "DCMotor.h"
#include "Ping.h"
#include "PID_v1.h"
#include "BatteryMonitor.h"

#define R_MOTOR_PWM 14
#define R_MOTOR_I1 12
#define R_MOTOR_I2 13
#define L_MOTOR_PWM 15
#define L_MOTOR_I1 17
#define L_MOTOR_I2 16
#define F_PING 
#define RF_PING
#define RB_PING
#define BAT_MON

class WallFollower
{
  public:
    WallFollower(byte speed, double wallOuter, double wallInner, double frontDistance);
	~WallFollower();
    void start();
	void stop();
	void setSpeed(byte speed);
	void setPerimeter(byte wallOuter, byte wallInner, byte frontDistance);
	DCMotor m_rightMotor;
	DCMotor m_leftMotor;
	Ping m_frontPing;
	Ping m_rightFrontPing;
	Ping m_rightBackPing;
	PID m_PID;
	double m_input;
	double m_output;
	double m_setPoint;
	double m_kp;
	double m_ki;
	double m_kd;
  private:
	double m_wallOuter;
	double m_wallInner;
 	byte m_speed;
	double m_frontDistance;
};

#endif

