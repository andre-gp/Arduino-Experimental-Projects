const int buzzerPin = 2;

const int potPin = A2;

int potMaxThreshold = 1000; 

void setup() {  
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  Serial.println(analogRead(potPin));
  digitalWrite(buzzerPin, analogRead(potPin) > potMaxThreshold ? HIGH : LOW);
}
