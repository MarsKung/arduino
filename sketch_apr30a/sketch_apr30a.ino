#include <AFMotor.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

AF_DCMotor motor_dc_1(1, MOTOR12_64KHZ);
AF_DCMotor motor_dc_2(2, MOTOR12_64KHZ);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
int times = 0;
#define R 44
#define CR 46
#define C 48
#define CL 50
#define L 52
#define drd digitalRead
// 描述此函數...
void forward() {
  motor_dc_1.setSpeed(200);
  motor_dc_1.run(FORWARD);
  motor_dc_2.setSpeed(200);
  motor_dc_2.run(FORWARD);
}

// 描述此函數...
void backward() {
  motor_dc_1.setSpeed(200);
  motor_dc_1.run(BACKWARD);
  motor_dc_2.setSpeed(200);
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
  motor_dc_1.setSpeed(200);
  motor_dc_1.run(BACKWARD);
  motor_dc_2.setSpeed(200);
  motor_dc_2.run(FORWARD);
}

// 描述此函數...
void right_turn_0() {
  motor_dc_1.setSpeed(200);
  motor_dc_1.run(FORWARD);
  motor_dc_2.setSpeed(200);
  motor_dc_2.run(BACKWARD);
}

void setup() {

  Serial.begin(9600);
}



void loop() {
  // float red, green, blue;
  // tcs.getRGB(&red, &green, &blue);
  // Serial.print("R:\t"); Serial.print(int(red));
  // Serial.print("\tG:\t"); Serial.print(int(green)); 
  // Serial.print("\tB:\t"); Serial.print(int(blue));
  // Serial.print("\n");
  int n = digitalRead(R);Serial.print(n)
  ;
  // if ((digitalRead(C) == 0 && digitalRead(CL) + digitalRead(L) + digitalRead(R) + digitalRead(CR) == 4) || digitalRead(CL) + digitalRead(L) + digitalRead(C) + digitalRead(R) + digitalRead(CR) == 5){
  //   forward();
  // } else if (digitalRead(CL) == 0 && digitalRead(C) + digitalRead(L) + digitalRead(R) + digitalRead(CR) == 4){
  //   left_turn_2();
  // } else if (digitalRead(CR) == 0 && digitalRead(C) + digitalRead(L) + digitalRead(R) + digitalRead(CL) == 4){
  //   right_turn_2();
  // } else if (digitalRead(L) == 0 && digitalRead(C) + digitalRead(CL) + digitalRead(R) + digitalRead(CR) == 4){
  //   left_turn_1();
  // } else if (digitalRead(R) == 0 && digitalRead(C) + digitalRead(L) + digitalRead(CR) + digitalRead(CL) == 4){
  //   right_turn_1();
  // } else {
  //   while (digitalRead(R) + digitalRead(C) + digitalRead(L) + digitalRead(CR) + digitalRead(CL) >= 2){
  //     Serial.print(times);
  //     Serial.print("\n");   
  //     delay(50);
  //   }
  //  times += 1;
  //}
}