/*
  Robot.cpp - Library for controlling something.
  Created by James King, Steve MacKinnon, and Sean Zensen March 19, 2013
*/

#include "Robot.h"

//constructor
Robot::Robot() :
	m_rightMotor(R_MOTOR_PIN, R_MOTOR_I1, R_MOTOR_I2, 165, 255),
	m_leftMotor(L_MOTOR_PIN, L_MOTOR_I1, L_MOTOR_I2, 165, 255),
	m_frontPing(F_PING),
	m_rightFrontPing(RF_PING),
	m_rightBackPing(RB_PING),
	m_batteryMonitor(BAT_MON,220000,100000)
	{
	TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
	}

Robot::~Robot(){
	
}