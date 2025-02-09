#include <Stepper.h>

int btnPin = 5;

int stepsPerRevolution = 2048; 
int motorSpeed = 10; // RPM

Stepper stepper(stepsPerRevolution, 8, 10, 9, 11);

int dir = 1;

int oldBtnVal = 1;
int newBtnVal = 1;

void setup() {
  Serial.begin(9600);

  stepper.setSpeed(motorSpeed);

  pinMode(btnPin, INPUT_PULLUP);
}

void loop() {
  stepper.step(1 * dir);

  newBtnVal = digitalRead(btnPin);

  if(newBtnVal == 0 && oldBtnVal == 1){
    dir *= -1;
  }

  oldBtnVal = newBtnVal;
}
