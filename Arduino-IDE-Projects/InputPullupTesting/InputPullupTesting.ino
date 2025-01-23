const int readPin = 6;

void setup() {
  Serial.begin(9600);

  // When using INPUT_PULLUP, if the circuit is opened, it will return 1 (5v)
  // If it is closed (connected to the GND), it will return 0
  // When INPUT_PULLUP is enabled, there's an internal resistor that is connected to the 5v 

  pinMode(readPin, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(readPin));  
}
