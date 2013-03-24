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

//f it, we'll do it live!
//pid variables
//double difference = 0;
//double setPoint = 0;
//double correction = 0;
//double aggKp=4, aggKi=0.2, aggKd=1;
//double consKp=1, consKi=0.05, consKd=0.25;

//global variables
double targetSpeed = 14;
double distance = 6;

//class constructors
DCMotor right = DCMotor(R_MOTOR_PWM, R_MOTOR_I1, R_MOTOR_I2, 165, 255);
DCMotor left = DCMotor(L_MOTOR_PWM, L_MOTOR_I1, L_MOTOR_I2, 165, 255);
Ping f_ping = Ping(F_PING);
Ping rf_ping = Ping(RF_PING);
Ping rb_ping = Ping(RB_PING);
BatteryMonitor batmon = BatteryMonitor(BAT_MON,220000,100000);
//PID myPID(&difference, &correction, &setPoint, 10, .2, 1, DIRECT); //f it, we'll do it live!

void setup() {
  Serial.begin(9600);
  TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
  //myPID.SetMode(AUTOMATIC); //f it, we'll do it live!
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
  //difference = rf_ping.inches() - rb_ping.inches(); //f it, we'll do it live!
  Serial.print("Front: ");
  Serial.print(rf_ping.inches());
  Serial.print("  ");
  Serial.print("Back: ");
  Serial.print(rb_ping.inches());
  Serial.println();
  //Serial.print("Difference: "); //f it, we'll do it live!
  //Serial.println(difference);
  if((f_ping.inches() > distance*2) && (rf_ping.inches() > distance*2) && (rb_ping.inches() > distance*2)) //about to hit a wall
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(targetSpeed);
  }
  else if(f_ping.inches() < distance*2) //about to hit a wall
  {
    left.setReverse();
    left.setSpeed(0);
    right.setSpeed(targetSpeed*1.75);
    while(f_ping.inches() < distance*3)
    {
      f_ping.fire();
    }
    rf_ping.fire();
    rb_ping.fire();
    while(rb_ping.inches() > rf_ping.inches())
    {
     rb_ping.fire();
     rf_ping.fire(); 
    }
  }
  else if((rf_ping.inches() > (distance*2))) //wall disappears to the right
  {
    //delay(250);
    left.setForward();
    right.setReverse();
    right.setSpeed(0);
    left.setSpeed(targetSpeed*1.25);
  }
  else if(rf_ping.inches() < (distance*0.75)) //getting way too close to the wall
  {
    left.setReverse();
    //left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(0);
  }
  else if((rf_ping.inches() > distance && rf_ping.inches() < distance*1.5) && (rb_ping.inches() < distance && rb_ping.inches() > distance/2)) //away from the wall but still around 6
  {
    left.setForward();
    right.setForward();
    left.setSpeed(targetSpeed*0.85);
    right.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() < distance && rf_ping.inches() > distance/2) && (rb_ping.inches() > distance && rb_ping.inches() < distance*1.5))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed*0.85);
    left.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() > distance) && (rb_ping.inches() < distance/2)) //away from the wall but front too far
  {
    left.setForward();
    right.setForward();
    left.setSpeed(targetSpeed);
    right.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() < distance/2) && (rb_ping.inches() > distance))
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(targetSpeed*0.15);
  }
  else if((rf_ping.inches() > distance) && (rb_ping.inches() > distance)) //way too far
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed*0.15);
    left.setSpeed(targetSpeed);
  }
  else if((rf_ping.inches() < distance) && (rb_ping.inches() < distance)) //way too close
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(targetSpeed*0.15);
  }
  /*else
  {
    left.setForward();
    right.setForward();
    right.setSpeed(targetSpeed);
    left.setSpeed(targetSpeed);
  }*/
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
  /*else{ //f it, we'll do it live!
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
