const int photoResistorPin = A6;
const int ledPin = 4;

const int TURN_ON_LIGHT_THRESHOLD = 400;

void setup() {
  pinMode(ledPin, OUTPUT);

}

void loop() {
  int resValue = analogRead(photoResistorPin);

  digitalWrite(ledPin, resValue > TURN_ON_LIGHT_THRESHOLD ? HIGH : LOW);

}
