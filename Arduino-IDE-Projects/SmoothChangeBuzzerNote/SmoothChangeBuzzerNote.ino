const int noteDelayPotPin = A2;
const int betweenDelayPotPin = A6;
const int buzzerPin = 2;

const int MIN_BUZZER_NOTE_DELAY = 60;
const int MAX_BUZZER_NOTE_DELAY = 10000;

const int MIN_BUZZER_BETWEEN_DELAY = 10;
const int MAX_BUZZER_BETWEEN_DELAY = 600;

void setup() {
  Serial.begin(9600);

  pinMode(noteDelayPotPin, INPUT);
  pinMode(betweenDelayPotPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

int getDelay(float potVal, float minVal, float maxVal){
  return (((maxVal - minVal) / 1023.) * potVal) + minVal;
}

void loop() {

  int noteDelay = getDelay(analogRead(noteDelayPotPin), MIN_BUZZER_NOTE_DELAY, MAX_BUZZER_NOTE_DELAY);
  //Serial.println(noteDelay);
 
  
  for (int i = 0; i < 30; i++) 
  {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(noteDelay);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(noteDelay);
  }

  int betweenDelay = getDelay(analogRead(betweenDelayPotPin), MIN_BUZZER_BETWEEN_DELAY, MAX_BUZZER_BETWEEN_DELAY);
  Serial.println(betweenDelay);
  delay(betweenDelay);


}
