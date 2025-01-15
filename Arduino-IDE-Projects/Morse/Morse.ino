#define RED 2
#define GREEN 3
#define YELLOW 4

#define MORSE_DOT_TIME 200

/* 
  There are rules to help people distinguish dots from dashes in Morse code:
  The length of a dot is 1 time unit.
  A dash is 3 time units.
  The space between symbols (dots and dashes) of the same letter is 1 time unit.
  The space between letters is 3 time units.
  The space between words is 7 time units.
*/

void setup() {
  Serial.begin(9600);

  for (uint8_t i = 2; i <= YELLOW; ++i) {
    Serial.println(i);
    pinMode(i, OUTPUT);
  }
}

void blinkLED(uint8_t pin, unsigned long onDelay, unsigned long offDelay, uint8_t times)
{
  for (uint8_t i = 0; i < times; ++i) {
    digitalWrite(pin, HIGH);
    delay(onDelay);
    digitalWrite(pin, LOW);
    delay(offDelay);
  }
}

void blinkAll(){
  delay(1000);

  blinkLED(RED, 250, 250, 5);

  delay(1000);

  blinkLED(GREEN, 500, 50, 10);

  delay(1000);

  blinkLED(YELLOW, 50, 500, 15);
}

void loop() {
  blinkLED(RED, MORSE_DOT_TIME, MORSE_DOT_TIME, 3);
  delay(MORSE_DOT_TIME * 3);
  blinkLED(RED, MORSE_DOT_TIME * 3, 100, 3);
  delay(MORSE_DOT_TIME * 3);
  blinkLED(RED, MORSE_DOT_TIME, MORSE_DOT_TIME, 3);
  delay(MORSE_DOT_TIME * 7);
}
