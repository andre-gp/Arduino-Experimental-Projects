#include <Arduino.h>

#include <Servo.h>

#define SERVO_PIN 9
#define POT_PIN A3

Servo servo;

void setup() {
	servo.attach(SERVO_PIN);
}

void loop() {
	int potVal = analogRead(POT_PIN);
	int servoAngle = map(potVal, 0, 1023, 0, 170);
	servo.write(servoAngle);
	
	//delay(10);
}

