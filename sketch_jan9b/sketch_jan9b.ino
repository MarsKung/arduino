const int buzzerPin = 9; // 定義蜂鳴器腳位
bool dead = true;
bool roadup = false;
bool endup = false;
bool startup = false;

void setup(){
  Serial.begin(9600); // 初始串列通訊
  pinMode(7, INPUT);
  pinMode(10, OUTPUT);
  pinMode(4, INPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  pinMode(buzzerPin, OUTPUT); // 設定蜂鳴器為輸出
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(7, HIGH); 
  digitalWrite(4, HIGH); 
  digitalWrite(2, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void loop(){
  int start = digitalRead(4);
  int road = digitalRead(7);
  int end = digitalRead(2);

  // debug
  Serial.print("eoad: ");
  Serial.print(start);
  Serial.print(" | start: ");
  Serial.println(road);
  Serial.print(" | end: ");
  Serial.println(end);

  if(start == HIGH && startup == true){
    dead = false;
    startup = false;
    roadup = false;
    noTone(buzzerPin);
    digitalWrite(10, LOW);
    delay(200);
  }else if(start == LOW && startup == false){
    startup = true;
  }
  
  if(road == HIGH && roadup == true && dead == false){
    dead = true;
    roadup = false;
    startup = false;
    tone(buzzerPin, 1000);
    delay(200);
  }else if(road == LOW && roadup == false && dead == false){
    roadup = true;
  }
  if(end == HIGH && endup == true && dead == false){
    endup = false;
    startup = false;
    digitalWrite(10, HIGH);
  }else if(end == LOW && endup == false && dead == false){
    endup = true;
  }
}
