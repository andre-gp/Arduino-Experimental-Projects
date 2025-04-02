#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

#define CORRECT_PIN 7
#define ERROR_PIN 8

MFRC522 mfrc522(SS_PIN, RST_PIN);

byte blueCard = 252;

bool isCard(const MFRC522::Uid& uid, byte comparison){
  return uid.uidByte[0] == comparison;
}

void setup() {
  pinMode(ERROR_PIN, OUTPUT);
  pinMode(CORRECT_PIN, OUTPUT);

  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init RFID module
}

void loop() {
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++){
    key.keyByte[i] = 0xFF;
  }

  byte block;
  byte len;
  MFRC522::StatusCode status;

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("Began Detecting"));

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println();

  if(isCard(mfrc522.uid, blueCard)){
    Serial.println("Its the blue card!");
    
    digitalWrite(CORRECT_PIN, HIGH);
    
    delay(200);
    
    digitalWrite(CORRECT_PIN, LOW);
  } else{
    digitalWrite(ERROR_PIN, HIGH);
    
    delay(200);
    
    digitalWrite(ERROR_PIN, LOW);    
  }

  //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  delay(1000);
  
}
