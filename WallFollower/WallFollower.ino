#include <DCMotor.h>
#include <Ping.h>
#include <BatteryMonitor.h>
#include <PID_v1.h>

//pin defs
byte R_MOTOR_PWM=14;
byte R_MOTOR_I1=12;
byte R_MOTOR_I2=13;
byte L_MOTOR_PWM=15;
byte L_MOTOR_I1=17;
byte L_MOTOR_I2=16;
byte F_PING=1;
byte RF_PING=2;
byte RB_PING=3;
byte BAT_MON=4;

//pid variables
double difference = 0;
double setPoint = 0;
double correction = 0;
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

//global variables

//class constructors
DCMotor right = DCMotor(R_MOTOR_PWM, R_MOTOR_I1, R_MOTOR_I2, 165, 255);
DCMotor left = DCMotor(L_MOTOR_PWM, L_MOTOR_I1, L_MOTOR_I2, 165, 255);
Ping f_ping = Ping(F_PING);
Ping rf_ping = Ping(RF_PING);
Ping rb_ping = Ping(RB_PING);
BatteryMonitor batmon = BatteryMonitor(BAT_MON,220000,100000);
PID myPID(&difference, &correction, &setPoint, 10, 0, 0, DIRECT);

void setup() {
  TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0,100);
  right.setSpeed(5);
  left.setSpeed(5);
  right.setForward();
  left.setForward();
}

void loop() {
  byte temp=0;
  f_ping.fire();
  rf_ping.fire();
  rb_ping.fire();
  difference = rf_ping.inches() - rb_ping.inches();
  if(f_ping.inches() < 12)
  {
    left.stop_slow();
    temp = right.currentSpeed();
    left.setSpeed(temp);
  }
  else{
    myPID.Compute();
    temp = left.currentSpeed() + correction;
    left.setSpeed(temp);
    temp = right.currentSpeed() - correction;
    right.setSpeed(temp);
  }
}
