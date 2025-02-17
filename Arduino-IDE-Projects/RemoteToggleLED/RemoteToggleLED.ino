#include "IRremote.hpp"
#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])

int receiverPin = 9;

int ledPin = 8;

int powers[] {8, 69};


bool isOn = false;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(receiverPin, true, LED_BUILTIN);  
  pinMode(ledPin, OUTPUT);
}

void loop() {

  if(IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.command);

    for (int i = 0; i < ARR_SIZE(powers); ++i) {
      if(IrReceiver.decodedIRData.command == powers[i])
      {
        digitalWrite(ledPin, !digitalRead(ledPin));
      }
    }
    
    
    delay(200);
    IrReceiver.resume();
  }
}
