#include <Arduino.h>
#include <MD_MAX72xx.h>

#define  DELAYTIME  120  //Controla a velocidade em que o texto se desloca
#define MODULES_NUM  1   
#define DATA_PIN  10  
#define CS_PIN    9  
#define CLK_PIN   8   

MD_MAX72XX leds(MD_MAX72XX::GENERIC_HW, DATA_PIN, CLK_PIN, CS_PIN, MODULES_NUM);

int currentNum = 0;

void setup() 
{
  leds.begin();
  leds.control(MD_MAX72XX::INTENSITY, 1);

  delay(2000);
}


void loop() // Loop principal
{
  leds.clear();
  leds.setRow(0, currentNum);
  currentNum += 1;
  delay(50);

  if(currentNum > 255)
  {
      while(1){}
  }
}
