#include "Keyboard.h"
#include "Mouse.h"

void setup() {
  delay(5000);
  // put your setup code here, to run once:
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Mouse.press();
  
  Mouse.move(sin(millis()) * 50, cos(millis()) * 50);
}
