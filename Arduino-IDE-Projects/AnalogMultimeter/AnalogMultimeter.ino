const int pin = A6;

void setup() {
  Serial.begin(9600);

  pinMode(pin, INPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  float value = analogRead(pin);
  float voltage = (5./1023.) * value;

  Serial.print("Raw Value: ");
  Serial.print(value);

  Serial.print(" ; Voltage: ");
  Serial.println(voltage);

  delay(100);
}
