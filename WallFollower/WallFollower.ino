#include <DCMotor.h>
#include <Ping.h>
#include <BatteryMonitor.h>
//#include <PID_v1.h>

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
//double difference = 0;
//double setPoint = 0;
//double correction = 0;
//double aggKp=4, aggKi=0.2, aggKd=1;
//double consKp=1, consKi=0.05, consKd=0.25;

//global variables
double targetSpeed = 20;
double distance = 6;

//class constructors
DCMotor right = DCMotor(R_MOTOR_PWM, R_MOTOR_I1, R_MOTOR_I2, 165, 255);
DCMotor left = DCMotor(L_MOTOR_PWM, L_MOTOR_I1, L_MOTOR_I2, 165, 255);
Ping f_ping = Ping(F_PING);
Ping rf_ping = Ping(RF_PING);
Ping rb_ping = Ping(RB_PING);
BatteryMonitor batmon = BatteryMonitor(BAT_MON,220000,100000);
//PID myPID(&difference, &correction, &setPoint, 10, .2, 1, DIRECT);

void setup() {
  Serial.begin(9600);
  TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
  //myPID.SetMode(AUTOMATIC);
  //myPID.SetOutputLimits(-targetSpeed*4,targetSpeed*4);
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
  //difference = rf_ping.inches() - rb_ping.inches();
  Serial.print("Front: ");
  Serial.print(rf_ping.inches());
  Serial.print("  ");
  Serial.print("Back: ");
  Serial.print(rb_ping.inches());
  Serial.println();
  Serial.print("Difference: ");
  Serial.println(difference);
  if(f_ping.inches() < distance*2)
  {
    left.setReverse();
    left.setSpeed(0);
    right.setSpeed(targetSpeed*1.5);
    while(f_ping.inches() < distance*2)
    {
      f_ping.fire();
    }
  }
  else if((rf_ping.inches() > (distance*3)))
  {
    left.setForward();
    right.setReverse();
    right.setSpeed(0);
    left.setSpeed(targetSpeed*1.5);
  }
  else if(rf_ping.inches() < distance/2)
  {
    left.setReverse();
    right.setForward();
    right.setSpeed(targetSpeed*1.5);
    left.setSpeed(0);
  }
  else if((rf_ping.inches() > distance) && (rb_ping.inches() < distance))
  {
    left.setForward();
    right.setForward();
    left.setSpeed(targetSpeed);
    right.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() > distance+1) && (rb_ping.inches() < distance+1))
  {
    left.setForward();
    right.setForward();
    left.setSpeed(targetSpeed*1.25);
    right.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() < distance) && (rb_ping.inches() < distance))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() < distance-1) && (rb_ping.inches() < distance-1))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed*1.25);
    left.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() < distance) && (rb_ping.inches() > distance))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() < distance-1) && (rb_ping.inches() > distance+1))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed*1.5);
    left.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() > distance) && (rb_ping.inches() > distance))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed*0.15);
    left.setSpeed(targetSpeed);
  }
  else if((rf_ping.inches() > distance+1) && (rb_ping.inches() > distance+1))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed*0.15);
    left.setSpeed(targetSpeed*1.25);
  }
  else
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(targetSpeed);
  }
  /*else if((rb_ping.inches() > 4) && (rf_ping.inches() > 4))
  {
    left.setSpeed(targetSpeed + targetSpeed);
    right.setSpeed(targetSpeed);    
  }
  else if((rf_ping.inches() < 2) && (rb_ping.inches() < 2))
  {
    left.setSpeed(targetSpeed);
    right.setSpeed(targetSpeed + targetSpeed);
  }*/
  /*else{
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
  }*/
  delay(50);
}
