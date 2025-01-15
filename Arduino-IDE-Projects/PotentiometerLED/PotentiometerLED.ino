
void setup() {
  Serial.begin(9600);

  pinMode(A1, INPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  float V = (5./1023.) * analogRead(A1);

  Serial.println(V);

  digitalWrite(8, V > 4 ? HIGH : LOW);

  delay(100);
}
