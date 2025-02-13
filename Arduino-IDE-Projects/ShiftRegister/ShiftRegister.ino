int clockPin = 9;
int latchPin = 11;
int dataPin = 12;

byte LEDs = B001001;

void setup() {
  Serial.begin(9600);

  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, LEDs);
  digitalWrite(latchPin, HIGH);
}

void loop() {
  

}
