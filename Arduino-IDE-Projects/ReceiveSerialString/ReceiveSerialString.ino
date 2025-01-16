#define ARR_LEN(array) sizeof(array)/sizeof(array[0]) 

constexpr int ledPins[] {4,5,6};
const String inputs[] {"red","green","blue"};

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < ARR_LEN(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void turnLED(int index){
  for (int i = 0; i < ARR_LEN(ledPins); i++) {
    digitalWrite(ledPins[i], i == index ? HIGH : LOW);
  }
}

void toggleLED(int index){
  for (int i = 0; i < ARR_LEN(ledPins); i++) {
    if(i == index)
      digitalWrite(ledPins[i], !digitalRead(ledPins[i]));
  }
}

void loop() {
  Serial.println("Select a LED to turn on: [red, blue, built]");

  while (!Serial.available()) {
  
  }

  String userInput = Serial.readString();

  Serial.print("Received Input: ");
  Serial.println(userInput);

  bool foundInput = false;

  for (int i = 0; i < ARR_LEN(inputs); i++) {
    if(userInput == inputs[i]){
      toggleLED(i);
      foundInput = true;
      break;
    }
  }

  if(!foundInput){
    Serial.println("Invalid Input!");
    turnLED(-1);
  }

  delay(2000);
}
