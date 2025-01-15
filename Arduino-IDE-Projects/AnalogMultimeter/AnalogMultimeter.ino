
void setup() {
  Serial.begin(9600);

  pinMode(A1, INPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  float V = analogRead(A1);

  Serial.println((5./1023.) * V);

  digitalWrite(8, V > 4 ? HIGH : LOW);

  delay(100);
}
