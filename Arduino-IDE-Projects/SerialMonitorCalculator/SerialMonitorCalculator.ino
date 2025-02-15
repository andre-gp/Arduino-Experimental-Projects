#include <LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void waitInput(){
  while (!Serial.available()) {
  
  }
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Type 1st number:");
  waitInput();
  int num1 = Serial.parseInt();

  lcd.clear();
  lcd.print("Type operator");
  waitInput();
  String operation = Serial.readString();

  lcd.clear();
  lcd.print("Type 2nd number: ");
  waitInput();
  int num2 = Serial.parseInt();
  
  int result = 0;

  if(operation == "+")
    result = num1 + num2;
  if(operation == "-")
    result = num1 - num2;
  if(operation == "*")
    result = num1 * num2;
  if(operation == "/")
    result = num1 / num2;

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Result:");
  lcd.setCursor(0, 1);
  lcd.print(num1);
  lcd.print(operation);
  lcd.print((num2));
  lcd.print(" = ");
  lcd.print(result);

  delay(8000);
}
