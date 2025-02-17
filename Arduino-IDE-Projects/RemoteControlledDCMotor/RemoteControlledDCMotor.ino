#include "IRremote.h"

/* Remote macros */
#define BTN_POWER 69
#define BTN_PAUSE 64
#define BTN_INCREASE_SPEED 67
#define BTN_DECREASE_SPEED 68
#define BTN_REVERSE 21
#define BTN_RIGHT_DIR 9
#define BTN_LEFT_DIR 7

/* Receiver pin */
int receiverPin = 9;

/* DC Motor pins */
int speedPin = 5;
int dir1Pin = 4;
int dir2Pin = 3;

bool isOn = false;

int currentSpeed = 150; // 100-255

bool currentDirection = true;


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(receiverPin);

  pinMode(speedPin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);

  changeDirection(currentDirection);

  changeSpeed(isOn, currentSpeed);
}

void changeSpeed(bool newIsOn, uint8_t speed){
  isOn = newIsOn;

  analogWrite(speedPin, isOn ? speed : 0);

  Serial.print("Speed: ");
  Serial.println(speed);
}

void changeDirection(bool isGoingRight){
  digitalWrite(dir1Pin, isGoingRight);
  digitalWrite(dir2Pin, !isGoingRight);
  currentDirection = isGoingRight;
}

void toggleDirection(){
  changeDirection(!currentDirection);
}

void processCommand(uint16_t cmd){
  if(cmd == BTN_POWER || cmd == BTN_PAUSE){
    changeSpeed(!isOn, currentSpeed);

    delay(100);    
  }

  if(cmd == BTN_INCREASE_SPEED){
    currentSpeed += 2;

    if(currentSpeed >= 255)
      currentSpeed = 255;

    changeSpeed(isOn, currentSpeed);
  }

   if(cmd == BTN_DECREASE_SPEED){
    currentSpeed -= 2;

    if(currentSpeed <= 0)
      currentSpeed = 0;

    changeSpeed(isOn, currentSpeed);
  }

  if(cmd == BTN_REVERSE){
    toggleDirection();

    delay(100);
  }

  if(cmd == BTN_RIGHT_DIR){
    changeDirection(true);
  }

  if(cmd == BTN_LEFT_DIR){
    changeDirection(false);
  }

}

void loop() {
  
  if(IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.command);
    processCommand(IrReceiver.decodedIRData.command);

    IrReceiver.resume();
  }
  return;
}
