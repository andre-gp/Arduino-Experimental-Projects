#include "Keyboard.h"

#define SENSOR_PIN A2

#define THRESHOLD 600

bool isOn;



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Keyboard.begin();

  isOn = readVal();
}

bool readVal(){
  //Serial.println(analogRead(SENSOR_PIN));
  return analogRead(SENSOR_PIN) > THRESHOLD;
}

void loop() {

  if(isOn != readVal()){
    isOn = readVal();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_TAB);

    Keyboard.release(KEY_LEFT_ALT);
    Keyboard.release(KEY_TAB);

    delay(400);
  }
}
