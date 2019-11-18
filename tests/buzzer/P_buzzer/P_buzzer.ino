int buzzer = D3;                       // buzzer을 9로 설정합니다.

void setup() {
  pinMode(buzzer, OUTPUT);            // buzzer를 출력핀으로 설정합니다.
}

void loop() {
  digitalWrite(buzzer, HIGH);
  delay(1000);                        // buzzer에 1초간 HIGH를 출력합니다.
  digitalWrite(buzzer, LOW);
  delay(1000);                        // buzzer에 1초간 LOW를 출력합니다.
  digitalWrite(buzzer, HIGH);
  delay(500);                         // buzzer에 0.5초간 HIGH를 출력합니다.
  digitalWrite(buzzer, LOW);
  delay(500);                         // buzzer에 0.5초간 LOW를 출력합니다.
}
