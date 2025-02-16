#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

// Sensor pins
int triggerPin = 6; // I had a problem when connecting the sensor pins to pin 10-12.
int echoPin = 7;    // I later discovered that those pins are used with the SPI comms
                    // Even if there isn't anything plugged in directly in them.

// OLED Pins
#define TFT_CS        2
#define TFT_RST       4 
#define TFT_DC        3

#define TEXT_COLOR ST77XX_BLACK
#define BG_COLOR ST77XX_WHITE

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

float previousDistance;

void setup() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);

    tft.initR(INITR_BLACKTAB); 
    delay(100);  // Ensure display initializes

    tft.fillScreen(BG_COLOR);

    tft.setTextSize(1);
    tft.setTextColor(TEXT_COLOR);
    tft.setCursor(40, 30);
    tft.println("Distance:");

    tft.setTextSize(2);
    tft.setCursor(50, 90);
    tft.println("cm");
}

void startDetectingDistance(){
digitalWrite(triggerPin, LOW);
  delayMicroseconds(10);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
}

void loop() {
  startDetectingDistance();

  float time = pulseIn(echoPin, HIGH, 10000);
  float distance = (time * 0.0343) / 2; // Convert to cm

  delay(200);

  if(distance <= 0.01)
    return;

  Serial.println(distance, 20);

  tft.setTextSize(2);
  tft.setCursor(38, 60);
  tft.setTextColor(BG_COLOR);
  tft.println(previousDistance);

  previousDistance = distance;

  tft.setTextSize(2);
  tft.setCursor(38, 60);
  tft.setTextColor(TEXT_COLOR);
  tft.println(distance);

  // Serial.print(0);
  // Serial.print(",");
  // Serial.print(distance);
  // Serial.print(",");
  // Serial.println(20);
}