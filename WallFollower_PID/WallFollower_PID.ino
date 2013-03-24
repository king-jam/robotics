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
byte F_PING=0;
byte RF_PING=11;
byte RB_PING=1;
byte BAT_MON=21;

//pid variables
double difference = 0;
double setPoint = 0;
double correction = 0;
double ku=50;
double tu=5;
double kp=0.2*ku;
//double ki=(2*kp)/tu;
double ki=0;
//double kd=(kp*tu)/3;
double kd=0.25;

//global variables
double targetSpeed = 10;
double distance = 6;

//class constructors
DCMotor right = DCMotor(R_MOTOR_PWM, R_MOTOR_I1, R_MOTOR_I2, 165, 255);
DCMotor left = DCMotor(L_MOTOR_PWM, L_MOTOR_I1, L_MOTOR_I2, 165, 255);
Ping f_ping = Ping(F_PING);
Ping rf_ping = Ping(RF_PING);
Ping rb_ping = Ping(RB_PING);
BatteryMonitor batmon = BatteryMonitor(BAT_MON,220000,100000);
PID myPID(&difference, &correction, &setPoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600);
  TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-targetSpeed*3,targetSpeed*3);
  //myPID.SetOutputLimits(-90,90);
  right.setSpeed(targetSpeed);
  left.setSpeed(targetSpeed);
  right.setForward();
  left.setForward();
}

void loop() {
  int temp=0;
  rf_ping.fire();
  f_ping.fire();
  rb_ping.fire();
  difference = rf_ping.inches() - rb_ping.inches() + rf_ping.inches() - distance;
  Serial.print("Front: ");
  Serial.print(rf_ping.inches());
  Serial.print("  ");
  Serial.print("Back: ");
  Serial.print(rb_ping.inches());
  Serial.println();
  Serial.print("Difference: "); //f it, we'll do it live!
  Serial.println(difference);
  if(f_ping.inches() < distance*2.5) //about to hit a wall
  {
    left.setReverse();
    left.setSpeed(0);
    right.setSpeed(targetSpeed*1.5);
    while(f_ping.inches() < distance*3)
    {
      rf_ping.fire();
      f_ping.fire();
      rb_ping.fire();
      difference = rf_ping.inches() - rb_ping.inches() + rf_ping.inches() - distance;
      myPID.Compute();
    }
    f_ping.fire();
    rf_ping.fire();
    rb_ping.fire();
    difference = rf_ping.inches() - rb_ping.inches() + rf_ping.inches() - distance;
    myPID.Compute();
    while(rb_ping.inches() > rf_ping.inches())
    {
     rb_ping.fire();
     f_ping.fire();
     rf_ping.fire();
     difference = rf_ping.inches() - rb_ping.inches() + rf_ping.inches() - distance;
     myPID.Compute();
    }
    left.setForward();
  }
  else{
    myPID.Compute();
    Serial.print("Correction: ");
    Serial.println(correction);
    temp = targetSpeed - (int) correction;
    Serial.print("Left: ");
    Serial.print(temp);
    Serial.print("  ");
    left.setSpeed(temp);
    temp = 0;
    temp = targetSpeed + (int) correction;
    Serial.print("Right: ");
    Serial.print(temp);
    Serial.println();
    right.setSpeed(temp);
  }
}
