int VRY = A1;
int VRX = A2;
int SW = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  int y = analogRead(VRY);
  int x = analogRead(VRX);

  Serial.print("SW: ");
  Serial.println(digitalRead(SW));
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);



  delay(100);
}
