/*
  WallFollower.cpp - Library for controlling something.
  Created by James King, Steve MacKinnon, and Sean Zensen March 19, 2013
*/

#include "WallFollower.h"

//constructor	- PWM Pin - H-Bridge I1 - H-Bridge I2 - Low PWM Limit - High PWM Limit
WallFollower::WallFollower(byte speed, double wallOuter, double wallInner, double frontDistance) :
	m_rightMotor(R_MOTOR_PIN, R_MOTOR_I1, R_MOTOR_I2, 165, 255),
	m_leftMotor(L_MOTOR_PIN, L_MOTOR_I1, L_MOTOR_I2, 165, 255),
	m_wallOutter(wallOutter)
	m_wallInner(wallInner),
	m_frontDistance(frontDistance),
	m_frontPing(F_PING),
	m_rightFrontPing(RF_PING),
	m_rightBackPing(RB_PING),
	m_PID(&m_input, &m_output, &m_setPoint, m_kp, m_ki, m_kd, DIRECT),
	m_isRunning(false) {
	
	m_PID.SetMode(AUTOMATIC);
	
	}

WallFollower::~WallFollower(){
	
}

void WallFollower::start(){

}

void WallFollower::stop(){

}
void WallFollower::setSpeed(byte speed){

}

void WallFollower::setPerimeter(byte wallOuter, byte wallInner, byte frontDistance){

}