#define LED_PIN 3

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  Serial.println("Type the number of times that the LED should blink.");

  while (!Serial.available()) {

  }

  int numberInput = Serial.parseInt();

  Serial.print("Will blink ");
  Serial.print(numberInput);
  Serial.println(" times.");
  
  for (int i = 0; i < numberInput; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
}
