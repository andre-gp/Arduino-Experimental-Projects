#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <snakeGameModule.h>

// Buzzer
#define BUZZER_PIN 2
#define SOUND_DURATION 200

bool isPlayingSound = false;
unsigned long soundStartTime; 

// W A S D
uint8_t pins[] = {4, 7, A5, A2 };
Vector2 directions[] = {{-1, 0}, {0,1}, {1, 0}, {0, -1}};


#define  DELAYTIME  120  //Controla a velocidade em que o texto se desloca
#define MODULES_NUM  1   
#define DATA_PIN  10  
#define CS_PIN    9  
#define CLK_PIN   8   

MD_MAX72XX leds(MD_MAX72XX::GENERIC_HW, DATA_PIN, CLK_PIN, CS_PIN, MODULES_NUM);

int currentNum = 0;

SnakeGame snakeGame(Vector2{8,8}, 250, true);

bool onGetPoint(const Vector2& pos)
{
    soundStartTime = millis();
    isPlayingSound = true;    
    digitalWrite(BUZZER_PIN, HIGH);
}

bool onDraw(const Vector2& pos)
{
    leds.setPoint(pos.x, pos.y, true);
}

bool onErase(const Vector2& pos)
{
  leds.setPoint(pos.x, pos.y, false);
}

void setup() 
{
  Serial.begin(9600);
  
  pinMode(BUZZER_PIN, OUTPUT);
  
  for (size_t i = 0; i < 4; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }
  

  leds.begin();
  leds.control(MD_MAX72XX::INTENSITY, 1);


  snakeGame.getRenderEngine().BindFunctions(&onDraw, &onErase, &onGetPoint);

  snakeGame.startGame();

  
  delay(1500);
}

void loop()
{
  snakeGame.gameLoop();
  
  if(isPlayingSound && millis() > soundStartTime + SOUND_DURATION) 
  {
      isPlayingSound = false;
      digitalWrite(BUZZER_PIN, LOW);
  }

  for (size_t i = 0; i < 4; i++)
  {
    if(digitalRead(pins[i]) == LOW)
    {
        snakeGame.setDirection(directions[i]);
        
        Serial.println("Changed dir");
    }
  }
}
