#include <AFMotor.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

AF_DCMotor motor_dc_1(2, MOTOR12_64KHZ);
AF_DCMotor motor_dc_2(3, MOTOR34_64KHZ);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
int times = 0;
#define R 44
#define CR 46
#define C 48
#define CL 50
#define L 52
#define drd digitalRead
#define wait delay
#define turnTime 1650
#define speed 150
// 描述此函數...
void forward() {
  motor_dc_1.setSpeed(speed);
  motor_dc_1.run(FORWARD);
  motor_dc_2.setSpeed(speed);
  motor_dc_2.run(FORWARD);
}

// 描述此函數...
void backward() {
  motor_dc_1.setSpeed(speed);
  motor_dc_1.run(BACKWARD);
  motor_dc_2.setSpeed(speed);
  motor_dc_2.run(BACKWARD);
}

// 描述此函數...
void stop() {
  motor_dc_1.setSpeed(0);
  motor_dc_1.run(RELEASE);
  motor_dc_2.setSpeed(0);
  motor_dc_2.run(RELEASE);
}

// 描述此函數...
void left_turn_0() {
  motor_dc_1.setSpeed(speed);
  motor_dc_1.run(BACKWARD);
  motor_dc_2.setSpeed(speed);
  motor_dc_2.run(FORWARD);
}

// 描述此函數...
void right_turn_0() {
  motor_dc_1.setSpeed(speed);
  motor_dc_1.run(FORWARD);
  motor_dc_2.setSpeed(speed);
  motor_dc_2.run(BACKWARD);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int n = 0;
  while(!n){
    if(drd(L)&&drd(R))
      forward();
    else n=1;
  }
  
  if((drd(L)||drd(CL))&&!drd(C)){
    right_turn_0();
    delay(turnTime);
    forward();
  }
  if((drd(R)||drd(CR))&&!drd(C)){
    left_turn_0();
    delay(turnTime);
    forward();
  }
}