#define SENSOR A4

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR, INPUT);

}

void loop() {
  Serial.println(analogRead(SENSOR)); 
}
