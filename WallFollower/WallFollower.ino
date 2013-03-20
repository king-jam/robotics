#include <DCMotor.h>
#include <Ping.h>

byte R_MOTOR_PWM 14
byte R_MOTOR_I1 12
byte R_MOTOR_I2 13
byte L_MOTOR_PWM 15
byte L_MOTOR_I1 17
byte L_MOTOR_I2 16
byte F_PING 1
byte RF_PING 2
byte RB_PING 3
byte BAT_MON 4

DCMotor right = DCMotor(
void setup() {
  TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
}

void loop() {
  
}
