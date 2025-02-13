int tiltBallPin = A4;
int ledPin = 12;

int oldVal = 1;
int newVal = 1;


void setup() {
  Serial.begin(9600);
  pinMode(tiltBallPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  int analogVal = analogRead(tiltBallPin);

  if(analogVal < 16){
    newVal = 0;
  }
  else if(analogVal > 1022){
    newVal = 1;
  }
  else{
    return; // Is transitioning
  }

  digitalWrite(ledPin, newVal); 

  if(newVal != oldVal){
    delay(500);
  }

  oldVal = newVal;
}
