#include <DCMotor.h>
#include <Ping.h>
#include <PID_v1.h>

#define DEBUG 1

// Starting with using only 2 pings instead of 3 - 3 seems unnecessary

//pin defs
byte R_MOTOR_PWM=14;
byte R_MOTOR_I1=12;
byte R_MOTOR_I2=13;
byte L_MOTOR_PWM=15;
byte L_MOTOR_I1=17;
byte L_MOTOR_I2=16;
//byte F_PING=0;
byte R_PING=19;
byte L_PING=18;

//pid variables
double difference = 0;
double last_difference = 0;
double setPoint = 0;
double correction = 0;
double ku=75;
double tu=5;
double kp=0.2*ku;
//double ki=(2*kp)/tu;
double ki=0;
//double kd=(kp*tu)/3;
double kd=30;

//global variables
double targetSpeed = 11;
double distance = 5.5;
double sensitivity = 0.05;
bool is_lost = false;
bool use_pid = false;

//class constructors
DCMotor right = DCMotor(R_MOTOR_PWM, R_MOTOR_I1, R_MOTOR_I2, 155, 255);
DCMotor left = DCMotor(L_MOTOR_PWM, L_MOTOR_I1, L_MOTOR_I2, 155, 255);
Ping l_ping = Ping(L_PING);
Ping r_ping = Ping(R_PING);
PID myPID(&difference, &correction, &setPoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600);
  TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-targetSpeed*3.5,targetSpeed*3.5);
  right.setSpeed(targetSpeed);
  left.setSpeed(targetSpeed);
  right.setForward();
  left.setForward();
}

void loop() {
  
  if( use_pid) {
    myPID.Compute();
    difference = r_ping.inches() - l_ping.inches();
    Serial.print("difference: ");
    Serial.println(difference);
    Serial.print("correction: ");
    Serial.println(correction);
    int temp = targetSpeed - (int) correction;
    
    if(temp < 0)
    {
      temp = -temp;
      left.setReverse();
    }
    else
    {
      left.setForward();
    }
    //Serial.print("Left: ");
    //Serial.print(temp);
    //Serial.print("  ");
    left.setSpeed(temp);
    temp = 0;
    temp = targetSpeed + (int) correction;
    if(temp < 0)
    {
      temp = -temp;
      right.setReverse();
    }
    else
    {
      right.setForward();
    }
    right.setSpeed(temp); 
  }
  else {
    // Both pings < distance, stop both motors until one ping is far enough away
    bool l_stop = false;
    bool r_stop = false;
    l_ping.fire();
    r_ping.fire();
    Serial.print("L Inches: ");
    Serial.println(l_ping.inches());
    Serial.print("R Inches: ");
    Serial.println(r_ping.inches());
    
    if( l_ping.inches() < distance ) {
      Serial.println("LEFT STOP");
      left.setReverse();
      left.setSpeed(targetSpeed);
      l_stop = true;
    }
    if( r_ping.inches() < distance ) {
      Serial.println("RIGHT STOP");
      right.setReverse(); 
      right.setSpeed(targetSpeed);
      r_stop = true;
    }
    if( !l_stop && !r_stop ) {
      difference = r_ping.inches() - l_ping.inches();
      Serial.print("Difference: ");
      Serial.println(difference);
      
      float r_speed = targetSpeed * (1 + difference * sensitivity);
      float l_speed = targetSpeed * (1 - difference * sensitivity);
      
      Serial.print("L Speed: ");
      Serial.println(l_speed);
      Serial.print("R Speed: ");
      Serial.println(r_speed);
      
      right.setForward();
      right.setSpeed(targetSpeed * (1 + difference * sensitivity) );
      left.setForward();
      left.setSpeed(targetSpeed * (1 - difference * sensitivity) );
    }
    else if( !l_stop && r_stop ) {
      left.setForward();
      left.setSpeed(targetSpeed);  
    }
    else if( l_stop && !r_stop ) {
      right.setForward();
      right.setSpeed(targetSpeed);
    }
  }
}                                                           
