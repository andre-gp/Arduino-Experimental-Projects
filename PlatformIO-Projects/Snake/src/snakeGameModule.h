#include "vector2.h"

#define MAX_LENGTH 128

#define FUNC_DRAW_MACRO(OnEvent) bool (*OnEvent) (const Vector2& pos)

class RenderEngine
{
public:
    
    FUNC_DRAW_MACRO(OnDraw);
    FUNC_DRAW_MACRO(OnErase);

    void BindFunctions(FUNC_DRAW_MACRO(onDraw), FUNC_DRAW_MACRO(onErase))
    {
        /* Bind the functions of drawing and erasing to screen */
        OnDraw = onDraw;
        OnErase = onErase;
    }
};

class Snake
{
public:
    Snake()
    {
        
    }

    Snake(RenderEngine* renderEngine)
    {
        m_renderEngine = renderEngine;

        m_currentDirection = Vector2{-1,0};
    }

    void init(Vector2 headPosition, int length)
    {
        m_length = length;

        headPosition.x += length;

        for (size_t i = 0; i < length; i++)
        {
            positions[i] = headPosition + Vector2{-(int)i, 0};
            m_renderEngine->OnDraw(positions[i]);
            
        }
        
        m_tail = 0;
        m_head = length - 1;
    }

    void tick(bool willCollectFruit)
    {
        if(!willCollectFruit)
        {
            m_renderEngine->OnErase(positions[m_tail]);

            m_tail += 1;

            if(m_tail >= MAX_LENGTH)
            {
                m_tail = 0;
            }
        }

        Vector2 currentPosition = positions[m_head];
        currentPosition += m_currentDirection;

        m_head += 1;

        if(m_head >= MAX_LENGTH)
        {
            m_head = 0;
        }

        positions[m_head] = currentPosition;
        m_renderEngine->OnDraw(positions[m_head]);
    }

    void setDirection(const Vector2 dir)
    {
        int previous = m_head - 1;

        if(previous < 0)
            previous = 0;

        if((getCurrentHeadPos() + dir) == positions[previous])
        {
            return;
        }
        else
        {
            m_currentDirection = dir;
        }
    }

    const Vector2& getCurrentHeadPos() const { return positions[m_head]; } 
    const Vector2 nextPosition() const { return getCurrentHeadPos() + m_currentDirection; }

private:
    

    int m_length {0};

    int m_head{0};
    int m_tail{0};
    

    Vector2 m_currentDirection{};

    Vector2 positions[MAX_LENGTH];

    RenderEngine* m_renderEngine;
};



class SnakeGame
{
public:
    SnakeGame(const Vector2& dimensions, uint16_t tickMsTime)
        : m_dimensions { dimensions }
        , m_snake {&m_renderEngine}
        , m_tickTime {tickMsTime}
    {
        

    }

    void setDirection(const Vector2& dir)
    {
        m_snake.setDirection(dir);
    }

    RenderEngine& getRenderEngine()
    {
        return m_renderEngine;
    }

    void startGame()
    {
        m_snake.init(m_dimensions / 2, 3);

        GenerateFruit();
    }

    void GenerateFruit()
    {
        m_fruitPos = Vector2{random(0, m_dimensions.x),random(0, m_dimensions.y)};

        m_renderEngine.OnDraw(m_fruitPos);

        
    }

    void gameLoop()
    {
        if(millis() >= lastTick + m_tickTime)
        {
            lastTick = millis();

            

            if(m_snake.nextPosition() == m_fruitPos)
            {
                m_snake.tick(true);

                GenerateFruit();
            }
            else
            {
                m_snake.tick(false);
            }
        }        
    }

private:

    #pragma region Timing
    uint16_t m_tickTime{};
    unsigned long lastTick{};
    #pragma endregion

    #pragma region Snake Game
    Snake m_snake;

    Vector2 m_dimensions{};

    RenderEngine m_renderEngine{};

    Vector2 m_fruitPos;
    #pragma endregion
};

