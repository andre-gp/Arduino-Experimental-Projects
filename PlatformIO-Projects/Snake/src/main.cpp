#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <snakeGameModule.h>

/* TODO 
   - Game Over
   - Stop Spawning Fruit on body   
*/


#define  DELAYTIME  120  //Controla a velocidade em que o texto se desloca
#define MODULES_NUM  1   
#define DATA_PIN  10  
#define CS_PIN    9  
#define CLK_PIN   8   

MD_MAX72XX leds(MD_MAX72XX::GENERIC_HW, DATA_PIN, CLK_PIN, CS_PIN, MODULES_NUM);

int currentNum = 0;

SnakeGame snakeGame(Vector2{8,8}, 1000);

bool OnDraw(const Vector2& pos)
{
    leds.setPoint(pos.x, pos.y, true);
    return;
    Serial.print("Draw at ");
    Serial.print(pos.x);
    Serial.print(",");
    Serial.println(pos.y);
}

bool OnErase(const Vector2& pos)
{
  leds.setPoint(pos.x, pos.y, false);
}

void setup() 
{
  Serial.begin(9600);

  leds.begin();
  leds.control(MD_MAX72XX::INTENSITY, 1);

  delay(2000);

  snakeGame.getRenderEngine().BindFunctions(&OnDraw, &OnErase);

  snakeGame.startGame();
}

void loop()
{
  snakeGame.gameLoop();

  if(Serial.available())
  {
      int dir = Serial.parseInt();

      if(dir == 4)
      {
          snakeGame.setDirection({1, 0});
      }
      if(dir == 6)
      {
        snakeGame.setDirection({-1, 0});
      }

      if(dir == 8)
      {
        snakeGame.setDirection({0, 1});
      }

      if(dir == 2)
      {
        snakeGame.setDirection({0, -1});
      }
  }
}
