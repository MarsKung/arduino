#include <Servo.h>
#include <AFMotor.h>
Servo servo_9;
Servo servo_10;

AF_DCMotor motor_dc_1(2, MOTOR12_64KHZ);
AF_DCMotor motor_dc_2(3, MOTOR34_64KHZ);

void stop() {
  motor_dc_1.setSpeed(0);
  motor_dc_1.run(RELEASE);
  motor_dc_2.setSpeed(0);
  motor_dc_2.run(RELEASE);
}

void release(){
  motor_dc_1.setSpeed(150);
  motor_dc_1.run(FORWARD);
  motor_dc_2.setSpeed(150);
  motor_dc_2.run(FORWARD);
  delay(500);
  stop();
  delay(50);
  servo_10.write(180);
  delay(500);
  servo_10.write(90);
  servo_9.write(90);
}

void catching() {
  servo_9.write(130);
  servo_10.write(180);
  delay(500);
  motor_dc_1.setSpeed(150);
  motor_dc_1.run(FORWARD);
  motor_dc_2.setSpeed(150);
  motor_dc_2.run(FORWARD);
  delay(500);
  stop();
  delay(50);
  servo_10.write(90);
  delay(1000);
  servo_9.write(90);
  delay(1000);
}

void setup() {
  servo_9.attach(9);
  servo_10.attach(10);
  servo_9.write(90);
  delay(1000);
  servo_10.write(90);
  delay(1000);
}

void loop() {
  catching();
  delay(10000);
  release();
  delay(10000);

}