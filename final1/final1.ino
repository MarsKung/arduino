  #include <AFMotor.h>
  #include <Wire.h>
  #include "Adafruit_TCS34725.h"
  #include <Servo.h>
  #include <string.h>
  Servo servo_9;
  Servo servo_10;

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
  #define turnTime 600
  #define macro 10
  #define speed 200
  #define Aspot "A"
  #define Bspot "DD"
  #define Cspot "WD"

  char spot1[3][10]={"ACUAW","DDCUAD","WDCUD"};//GRY

  void release() {
    motor_dc_1.setSpeed(150);
    motor_dc_1.run(FORWARD);
    motor_dc_2.setSpeed(150);
    motor_dc_2.run(FORWARD);
    delay(500);
    stop();
    delay(50);
    servo_9.write(180);
    delay(500);
    servo_9.write(90);
    servo_10.write(90);
    servo_9.attach(9);
    servo_10.attach(10);
  }

  void uturn(){
    motor_dc_1.setSpeed(200);
    motor_dc_1.run(BACKWARD);
    motor_dc_2.setSpeed(200);
    motor_dc_2.run(FORWARD);
  }

  // 描述此函數...
  void forward() {
    motor_dc_1.setSpeed(speed);
    motor_dc_1.run(FORWARD);
    motor_dc_2.setSpeed(speed);
    motor_dc_2.run(FORWARD);
  }

  void stop() {
    motor_dc_1.setSpeed(0);
    motor_dc_1.run(RELEASE);
    motor_dc_2.setSpeed(0);
    motor_dc_2.run(RELEASE);
  }

  void catching() {
    servo_10.write(130);
    servo_9.write(180);
    delay(500);
    motor_dc_1.setSpeed(150);
    motor_dc_1.run(FORWARD);
    motor_dc_2.setSpeed(150);
    motor_dc_2.run(FORWARD);
    delay(500);
    stop();
    delay(50);
    servo_9.write(90);
    delay(500);
    servo_10.write(60);
  }

  // 描述此函數...
  void backward() {
    motor_dc_1.setSpeed(speed);
    motor_dc_1.run(BACKWARD);
    motor_dc_2.setSpeed(speed);
    motor_dc_2.run(BACKWARD);
  }

  // 描述此函數...
  void speed_stop() {
    motor_dc_1.setSpeed(0);
    motor_dc_1.run(RELEASE);
    motor_dc_2.setSpeed(0);
    motor_dc_2.run(RELEASE);
  }

  // 描述此函數...
  void right_turn_0() {
    motor_dc_1.setSpeed(speed);
    motor_dc_1.run(BACKWARD);
    motor_dc_2.setSpeed(speed + 50);
    motor_dc_2.run(FORWARD);
  }

  // 描述此函數...
  void left_turn_0() {
    motor_dc_1.setSpeed(speed + 50);
    motor_dc_1.run(FORWARD);
    motor_dc_2.setSpeed(speed);
    motor_dc_2.run(BACKWARD);
  }

  void setup() {
    servo_9.attach(9);
    servo_10.attach(10);
    servo_9.write(90);
    servo_10.write(90);
    Serial.begin(9600);
  }

  void smooth() {
    if (drd(L) + drd(CL) > drd(CR) + drd(R)) {
      right_turn_0();
      delay(macro);
      smooth();
    }
    if (drd(L) + drd(CL) < drd(CR) + drd(R)) {
      left_turn_0();
      delay(macro);
      smooth();
    }
    if (drd(C)) {
      smooth();
    }
  }
  //black = 0; white = 1
  //color : blue = 1; red = 2; green = 3
  void loop() {
    //初始化
    char movements[500];
    int len = 0;
    int n = 0, tr[2] = { R, L };
    while (drd(C) + drd(CL) + drd(CR) + drd(R) + drd(L) != 5) delay(10);
    delay(3000);
    //開始
    int color = 0,idx = 0;
    forward();
    delay(1000);
    backward();delay(200);
    stop();
    delay(1000);
    uturn();
    delay(1500);
    while(1)forward();

    float red, green, blue;
    tcs.getRGB(&red, &green, &blue);
    int colors[3][3] = {{110,113,62},{182,67,53},{139,87,43}};//GRY,1,2,3
    delay(400);
    backward();delay(400);
    for(int i = 0;i<3;i++){
      if(int(red)>=colors[i][0]&&int(green)>=colors[i][1]&&int(blue)>=colors[i][2]) color = i;
    }
    
    int i=0;while(spot1[color][i]!='\0'){
      movements[len]=spot1[color][i];
      i++;len++;
    } 
    movements[len]='\0';
    Serial.print('A');
    for (int i = 0; i < len; i++) {
      color = 0;
      if (movements[i] == 'A') n = 1;
      else if (movements[i] == 'D') n = 0;  

      while (drd(tr[n]) == 1 && (movements[i] != 'C' || movements[i] != 'R')) {
        Serial.print(" While");
        if (drd(tr[0]) && drd(tr[1]) && !(drd(CR) || drd(CL))) smooth();
        forward();
      }

      if (movements[i] == 'W') {
        while (drd(tr[0]) && drd(tr[1])) {
          forward();
        }
        forward();
        delay(50);
      } else if (movements[i] == 'A') {
        left_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'D') {
        right_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'U'){
        uturn();
        delay(1500);
        smooth();
      } else if (movements[i] == 'C') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        catching();
        right_turn_0();
        uturn();
      } else if (movements[i] == 'R') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        release();
        right_turn_0();
        uturn();
      }
    }
    stop();
    delay(1000);
    //l1 to l2 ----------------------------------------------------------------------------------------------------------------------------------------
    len = 0;
    i=0;
    char newmovements1[50] = "DAW";
    while(newmovements1[i]!='\0'){
      movements[len]=newmovements1[i];
      i++;len++;
    }
    for (int i = 0; i < len; i++) {
      color = 0;
      if (movements[i] == 'A') n = 1;
      else if (movements[i] == 'D') n = 0;  

      while (drd(tr[n]) == 1 && (movements[i] != 'C' || movements[i] != 'R')) {
        Serial.print(" While");
        if (drd(tr[0]) && drd(tr[1]) && !(drd(CR) || drd(CL))) smooth();
        forward();
      }

      if (movements[i] == 'W') {
        while (drd(tr[0]) && drd(tr[1])) {
          forward();
        }
        forward();
        delay(50);
      } else if (movements[i] == 'A') {
        left_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'D') {
        right_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'U'){
        uturn();
        delay(1500);
        smooth();
      } else if (movements[i] == 'C') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        catching();
        right_turn_0();
        uturn();
      } else if (movements[i] == 'R') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        release();
        right_turn_0();
        uturn();
      }
    }
    stop();
    delay(1000);
    // l2
    color = 0,idx = 0;
    while (drd(tr[n]) == 1)forward();
    backward();delay(200);
    tcs.getRGB(&red, &green, &blue);//GRY,1,2,3
    stop();
    color = 0;
    for(int i = 0;i<3;i++){
      if(int(red)>=colors[i][0]&&int(green)>=colors[i][1]&&int(blue)>=colors[i][2]) color = i;
    }
    delay(400);backward();delay(400);
    char newmovements2[3][50] = {"DWAWADWWDARUDAWWADWDW","DWAWADWWAADDRUWAWWDWADWDW","DWAWADWDRUWAWADWDW"};//GRY1 2 3
    i=0;while(spot1[color][i]!='\0'){
      movements[len]=newmovements2[color][i];
      i++;len++;
    }
    movements[len]='\0';
    for (int i = 0; i < len; i++) {
      color = 0;
      if (movements[i] == 'A') n = 1;
      else if (movements[i] == 'D') n = 0;  

      while (drd(tr[n]) == 1 && (movements[i] != 'C' || movements[i] != 'R')) {
        Serial.print(" While");
        if (drd(tr[0]) && drd(tr[1]) && !(drd(CR) || drd(CL))) smooth();
        forward();
      }

      if (movements[i] == 'W') {
        while (drd(tr[0]) && drd(tr[1])) {
          forward();
        }
        forward();
        delay(50);
      } else if (movements[i] == 'A') {
        left_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'D') {
        right_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'U'){
        uturn();
        delay(1500);
        smooth();
      } else if (movements[i] == 'C') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        catching();
        right_turn_0();
        uturn();
      } else if (movements[i] == 'R') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        release();
        right_turn_0();
        uturn();
      }
    }
    stop();
    delay(1000);
    // l2 to l3 ---------------------------------------------------------------------------
    len = 0;
    i=0;
    char newmovements3[50] = "AWD";
    while(newmovements3[i]!='\0'){
      movements[len]=newmovements3[i];
      i++;len++;
    }
    for (int i = 0; i < len; i++) {
      color = 0;
      if (movements[i] == 'A') n = 1;
      else if (movements[i] == 'D') n = 0;  

      while (drd(tr[n]) == 1 && (movements[i] != 'C' || movements[i] != 'R')) {
        Serial.print(" While");
        if (drd(tr[0]) && drd(tr[1]) && !(drd(CR) || drd(CL))) smooth();
        forward();
      }

      if (movements[i] == 'W') {
        while (drd(tr[0]) && drd(tr[1])) {
          forward();
        }
        forward();
        delay(50);
      } else if (movements[i] == 'A') {
        left_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'D') {
        right_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'U'){
        uturn();
        delay(1500);
        smooth();
      } else if (movements[i] == 'C') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        catching();
        right_turn_0();
        uturn();
      } else if (movements[i] == 'R') {
        while(1){
          forward();
          tcs.getRGB(&red, &green, &blue);
          if(int(red)>=94&&int(green)>=109&&int(blue)>=94)break;
        }
        speed_stop();
        release();
        right_turn_0();
        uturn();
      }
    }
    stop();
    delay(5000);
    //l3 to end ---------------------------------------------------------------------------------------------------
    len = 0;
    i=0;
    char newmovements4[50] = "";
    while(newmovements4[i]!='\0'){
      movements[len]=newmovements4[i];
      i++;len++;
    }
    for (int i = 0; i < len; i++) {
      color = 0;
      if (movements[i] == 'A') n = 1;
      else if (movements[i] == 'D') n = 0;  

      while (drd(tr[n]) == 1 && (movements[i] != 'C' || movements[i] != 'R')) {
        Serial.print(" While");
        if (drd(tr[0]) && drd(tr[1]) && !(drd(CR) || drd(CL))) smooth();
        forward();
      }

      if (movements[i] == 'W') {
        while (drd(tr[0]) && drd(tr[1])) {
          forward();
        }
        forward();
        delay(50);
      } else if (movements[i] == 'A') {
        left_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'D') {
        right_turn_0();
        delay(turnTime);
        smooth();
      } else if (movements[i] == 'U'){
        uturn();
        delay(1500);
        smooth();
      } else if (movements[i] == 'C') {
        speed_stop();
        catching();
        right_turn_0();
        uturn();
      } else if (movements[i] == 'R') {
        speed_stop();
        release();
        right_turn_0();
        uturn();
      }
    }
    stop();
    delay(1000000);
  }