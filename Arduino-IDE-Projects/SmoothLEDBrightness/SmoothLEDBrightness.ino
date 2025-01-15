#define BUTTON 2
#define LED 9

bool hasBegun = false;
int currentOutput;
bool direction = true;

void setup() {
  Serial.begin(9600);

  currentOutput = 0;
  pinMode(LED, OUTPUT);
  analogWrite(LED, 0);

  pinMode(BUTTON, INPUT);
}

void loop() {

  if(!hasBegun){

    if(digitalRead(BUTTON) == HIGH){
    hasBegun = true;
    }

    return;
  }
  

  currentOutput += direction ? 1 : -1;

  if(currentOutput > 100){
    currentOutput = 100;
    direction = false;
    }
  else if(currentOutput < 0){
    currentOutput = 0;
    direction = true;
  }

  delay(20);

  analogWrite(LED, currentOutput);
}
