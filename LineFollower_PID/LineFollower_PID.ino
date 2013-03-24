#include <DCMotor.h>
#include <Ping.h>
#include <PID_v1.h>

//pin defs
byte R_MOTOR_PWM=14;
byte R_MOTOR_I1=12;
byte R_MOTOR_I2=13;
byte L_MOTOR_PWM=15;
byte L_MOTOR_I1=17;
byte L_MOTOR_I2=16;
byte F_PING=0;
byte IR_EN=1;
byte IR_OUT0=2;
byte IR_OUT1=3;
byte IR_OUT2=4;
byte IR_OUT3=5;
byte IR_OUT4=6;
byte IR_OUT5=7;
byte IR_OUT6=8;
byte IR_OUT7=9;

//pid variables
double difference = 0;
double setPoint = 0;
double correction = 0;
double ku=100;
double tu=5;
double kp=0.2*ku;
//double ki=(2*kp)/tu;
double ki=0;
//double kd=(kp*tu)/3;
double kd=25;

//global variables
double targetSpeed = 5;
double distance = 6;
byte sensor_value = 0;
byte last_value = 0;

//class constructors
DCMotor right = DCMotor(R_MOTOR_PWM, R_MOTOR_I1, R_MOTOR_I2, 165, 255);
DCMotor left = DCMotor(L_MOTOR_PWM, L_MOTOR_I1, L_MOTOR_I2, 165, 255);
Ping f_ping = Ping(F_PING);
PID myPID(&difference, &correction, &setPoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600);
  TCCR1B = TCCR1B & 0b11111000 | 0x01; //set div 1 prescalar for motors
  myPID.SetMode(AUTOMATIC);
  irSensorSetup();
  myPID.SetOutputLimits(-targetSpeed*15,targetSpeed*15);
  right.setSpeed(targetSpeed);
  left.setSpeed(targetSpeed);
  right.setForward();
  left.setForward();
}

void loop() {
  int temp = 0;
  byte sensor_value = 0;
  sensor_value = irSensorRead();
  Serial.print("Sensor_Value: ");
  Serial.println(sensor_value);
  irSensorHandler(sensor_value);
  /*Serial.println(digitalRead(IR_OUT0));
  Serial.println(digitalRead(IR_OUT1));
  Serial.println(digitalRead(IR_OUT2));
  Serial.println(digitalRead(IR_OUT3));
  Serial.println(digitalRead(IR_OUT4));
  Serial.println(digitalRead(IR_OUT5));
  Serial.println(digitalRead(IR_OUT6));
  Serial.println(digitalRead(IR_OUT7));
  */
  f_ping.fire();
  if(f_ping.inches() < distance) //about to hit something
  {
    while(f_ping.inches() < distance)
    {
      left.stop_fast();
      right.stop_fast();
      f_ping.fire();
    }
    left.setSpeed(targetSpeed);
    right.setSpeed(targetSpeed);
  }
  else{
    myPID.Compute();
    Serial.print("Correction: ");
    Serial.println(correction);
    temp = targetSpeed - (int) correction;
    if(temp < 0)
    {
      temp = -temp;
      left.setReverse();
    }
    else
    {
      left.setForward();
    }
    Serial.print("Left: ");
    Serial.print(temp);
    Serial.print("  ");
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
    Serial.print("Right: ");
    Serial.print(temp);
    Serial.println();
    right.setSpeed(temp);
  }
  last_value = sensor_value;
  //delay(100);
}

void irSensorSetup()
{
  pinMode(IR_EN,OUTPUT);
  pinMode(IR_OUT0,INPUT);
  pinMode(IR_OUT1,INPUT);
  pinMode(IR_OUT2,INPUT);
  pinMode(IR_OUT3,INPUT);
  pinMode(IR_OUT4,INPUT);
  pinMode(IR_OUT5,INPUT);
  pinMode(IR_OUT6,INPUT);
  pinMode(IR_OUT6,INPUT);
  digitalWrite(IR_EN,HIGH);
}

byte irSensorRead()
{
  byte output = 0;
  output |= digitalRead(IR_OUT0);
  output |= (digitalRead(IR_OUT1) << 1);
  output |= (digitalRead(IR_OUT2) << 2);
  output |= (digitalRead(IR_OUT3) << 3);
  output |= (digitalRead(IR_OUT4) << 4);
  output |= (digitalRead(IR_OUT5) << 5);
  output |= (digitalRead(IR_OUT6) << 6);
  output |= (digitalRead(IR_OUT7) << 7);
  return output;
}

void irSensorHandler(byte sensor)
{
  //byte sensor_invert=~sensor;
  switch(sensor)
  {
    case B00011111:
    case B00111111:
    case B01111111:
      difference = -10;
      break;
    case B00001111:
      difference = -8;
      break;
    case B00000011:
    case B00000001:
    case B00000010:
      Serial.println("Case 1");
      difference = -6;
      break;
    case B00000111:
    case B00000110:
    case B00000100:
      Serial.println("Case 2");
      difference = -4;
      break;
    case B00001110:
    case B00001100:
      Serial.println("Case 3");
      difference = -2;
      break;
    case B00011100:
    case B00011000:
    case B00111000:
      Serial.println("Case 4");
      difference = 0;
      break;
    case B01110000:
    case B00110000:
      Serial.println("Case 5");
      difference = 2;
      break;
    case B11100000:
    case B01100000:
    case B00100000:
      Serial.println("Case 6");
      difference = 4;
      break;
    case B11000000:
    case B01000000:
    case B10000000:
      Serial.println("Case 7");
      difference = 6;
      break;
    case B11110000:
      difference = 8;
      break;
    case B11111000:
    case B11111100:
    case B11111110:
      difference = 10;
      break;
    default:
      Serial.println("Case 8");
      difference = 0;
      break;
  }                                                                               
}


