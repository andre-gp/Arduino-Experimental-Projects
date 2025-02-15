#include "DHT.h"
#include <LiquidCrystal.h>

#define Type DHT11

// LCD Pins
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;

// DHT Pin
int sensePin = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT sensor(sensePin, Type);

void setup() {
  lcd.begin(16, 2);
  sensor.begin();
}

void loop() {
  float humidity = sensor.readHumidity();
  float temp = sensor.readTemperature(false);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  //lcd.setCursor(0, 1);
  lcd.print(humidity);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  //lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.print(" C");

  delay(3000);
}
