#include <Arduino.h>

#include "LedControl.h"

LedControl lc = LedControl(12, 10, 11);

int tickTime = 300;

int x = 0;
int y = 0;

int rowCount = 8;
int columnCount = 8;

void setup() {
  Serial.begin(9600);

  // Wake the LED from sleep mode
  lc.shutdown(0, false);

  
}

void loop() {
  lc.setLed(0, x, y, true);
  delay(300);
  lc.setLed(0, x, y, false);
  
  x += 1;

  if(x >= rowCount){
    x = 0;
    y += 1;

    if(y >= columnCount){
      y = 0;
    }
  }
}