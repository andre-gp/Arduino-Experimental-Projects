int speedPin = 5;
int dir1Pin = 4;
int dir2Pin = 3;

int currentSpeed = 80; // 100-255

int decreaseSpeedPin = 10;
int increaseSpeedPin = 11;



void setup() {
  Serial.begin(9600);

  pinMode(speedPin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);

  pinMode(decreaseSpeedPin, INPUT_PULLUP);
  pinMode(increaseSpeedPin, INPUT_PULLUP);

  changeDirection(false);

  changeSpeed(currentSpeed);
}

void changeSpeed(uint8_t speed){
  analogWrite(speedPin, speed);

  Serial.println(speed);
}

void changeDirection(bool isGoingRight){
  digitalWrite(dir1Pin, isGoingRight);
  digitalWrite(dir2Pin, !isGoingRight);
}

void loop() {
  if(digitalRead(increaseSpeedPin) == LOW){
    currentSpeed += 1;

    if(currentSpeed >= 255)
      currentSpeed = 255;

    changeSpeed(currentSpeed);
  }

  if(digitalRead(decreaseSpeedPin) == LOW){
    currentSpeed -= 1;

    if(currentSpeed <= 0)
      currentSpeed = 0;
    
    changeSpeed(currentSpeed);
  }

  delay(20);
}
