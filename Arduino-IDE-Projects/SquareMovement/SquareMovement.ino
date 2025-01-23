#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        8 
#define TFT_DC         9

// color definitions
const uint16_t  Display_Color_Black        = 0x0000;
const uint16_t  Display_Color_Blue         = 0x001F;
const uint16_t  Display_Color_Red          = 0xF800;
const uint16_t  Display_Color_Green        = 0x07E0;
const uint16_t  Display_Color_Cyan         = 0x07FF;
const uint16_t  Display_Color_Magenta      = 0xF81F;
const uint16_t  Display_Color_Yellow       = 0xFFE0;
const uint16_t  Display_Color_White        = 0xFFFF;

#define Display_Background_Color Display_Color_Magenta

class Player{

public:
  Player(uint8_t speed, int startPosX, int startPosY, uint8_t width, uint8_t height, uint16_t color)
    : m_posX(startPosX)
    , m_posY(startPosY)
    , m_width(width)
    , m_height(height)
    , m_color(color)
    , m_speed(speed){
      
    }

  void Initialize(Adafruit_ST7735* tft){
    m_tft = tft;
    DrawPlayer();
  }

  void Move(int8_t x, int8_t y){
    ErasePlayer();

    m_posX += x * m_speed;
    m_posY += y * m_speed;

    DrawPlayer();
  }

private:
  uint8_t m_speed;

  int m_posX;
  int m_posY;

  uint8_t m_width;
  uint8_t m_height;

  uint16_t m_color;

  Adafruit_ST7735* m_tft; 

  void ErasePlayer(){
    DrawPlayer(Display_Background_Color);
  }

  void DrawPlayer(){
    DrawPlayer(m_color);
  }

  void DrawPlayer(uint16_t color){
    m_tft->fillRect(m_posX, m_posY, m_width, m_height, color);
    //m_tft->drawRoundRect(m_posX, m_posY, m_width, m_height, m_width, color);
  }
};

const int delayTime = 4000;

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Player player {5, 40, 80, 5, 5, Display_Color_Cyan};

void setup() {
  Serial.begin(9600);
  
  tft.initR(INITR_BLACKTAB);
  tft.invertDisplay(true);
  tft.setRotation(1);

  tft.fillScreen(Display_Background_Color);

  player.Initialize(&tft);
}

void loop() {
  while(!Serial.available()){

  }

  char dir = Serial.read();

  Serial.println(dir);

  switch(dir){
    case 'd':
      player.Move(-1, 0);
      break;
    case 'a':
      player.Move(1, 0);
      break;
    case 'w':
      player.Move(0, 1);
      break;
    case 's':
      player.Move(0, -1);
      break;
  }
  
}
