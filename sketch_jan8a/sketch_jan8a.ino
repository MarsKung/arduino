const int startPointPin = 5;  // 出發點腳位
const int endPointPin = 6;    // 終點腳位
const int probePin = 7;       // 路徑腳位
const int buzzerPin = 9;      // 無源蜂鳴器腳位
const int ledPin = 8;         // LED燈腳位

bool gameStarted = false;
bool gameOver = false;
bool pathTouched = false;

void setup() {
  pinMode(startPointPin, INPUT); // 設為輸入
  pinMode(endPointPin, INPUT);   // 設為輸入
  pinMode(probePin, INPUT);
  pinMode(buzzerPin, OUTPUT);       // 設為輸入
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);       // 設為輸出
  
  digitalWrite(LED_BUILTIN, LOW);
  noTone(buzzerPin);  // 蜂鳴器默認關閉
  digitalWrite(ledPin, LOW);     // LED默認關閉
  Serial.begin(9600);            // 開啟序列監視器
}

void loop() {
  int startPointState = digitalRead(startPointPin);
  int endPointState = digitalRead(endPointPin);
  int probeValue = digitalRead(probePin);
  // Debugging: 打印腳位狀態
  Serial.print("Start Point: "); Serial.println(startPointState);
  Serial.print("End Point: "); Serial.println(endPointState);
  Serial.print("Path: "); Serial.println(probeValue);

  // 遊戲開始條件
  if (startPointState == 1 && !gameStarted && !gameOver) {
    gameStarted = true;  // 遊戲開始
    gameOver = false;
    pathTouched = false;
    noTone(buzzerPin);   // 停止蜂鳴器
  }

  if (gameStarted && !gameOver) {
    // 檢查是否碰到路徑
    if(probeValue == 1) {
      gameOver = true;   // 遊戲結束
      pathTouched = true;
      tone(buzzerPin, 1000);  // 無源蜂鳴器發出1000Hz的聲音
    }

    // 檢查是否到達終點
    if (endPointState == 1 && !pathTouched) {
      gameStarted = false;
      digitalWrite(LED_BUILTIN, HIGH);   // 點亮LED燈
      delay(3000);                  // 點亮3秒鐘
      digitalWrite(LED_BUILTIN, LOW);    // 關閉LED燈
    }
  } 

  // 等待返回起點後重新開始
  if (gameOver && startPointState == 1) {
    gameStarted = false;
    gameOver = false;
    pathTouched = false;
    noTone(buzzerPin);   // 停止蜂鳴器
  }
}
