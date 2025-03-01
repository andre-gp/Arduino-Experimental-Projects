#include "vector2.h"

#define MAX_LENGTH 128

#define FUNC_DRAW_MACRO(OnEvent) bool (*OnEvent) (const Vector2& pos)

class RenderEngine
{
public:
    
    FUNC_DRAW_MACRO(OnDraw);
    FUNC_DRAW_MACRO(OnErase);
    FUNC_DRAW_MACRO(OnCollectFruit);

    void BindFunctions(FUNC_DRAW_MACRO(onDraw), FUNC_DRAW_MACRO(onErase), FUNC_DRAW_MACRO(onCollectFruit))
    {
        /* Bind the functions of drawing and erasing to screen */
        OnDraw = onDraw;
        OnErase = onErase;
        OnCollectFruit = onCollectFruit;
    }
};

class Snake
{
public:
    Snake()
    {
        
    }

    Snake(RenderEngine* renderEngine, Vector2 dimensions, bool wrapped)
        : m_dimensions{dimensions}
        , m_wrapped{wrapped}
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
        else
        {
            m_length += 1;
        }

        Vector2 nextPosition = getNextPosition();

        m_head += 1;

        if(m_head >= MAX_LENGTH)
        {
            m_head = 0;
        }

        positions[m_head] = nextPosition;
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

    const Vector2 getCurrentHeadPos() const { return positions[m_head]; } 

    const Vector2 getNextPosition() const 
    { 
        Vector2 nextPos = getCurrentHeadPos() + m_currentDirection;
        
        if(!m_wrapped)
        {
            return nextPos;
        }
        else
        {
            nextPos.x = wrapPos(nextPos.x, m_dimensions.x);
            nextPos.y = wrapPos(nextPos.y, m_dimensions.y);

            return nextPos;
        }
    }

    

    bool isOccupied(const Vector2& pos)
    {
        int i = m_head;

        if(positions[m_tail] == pos)
        {
            return true;
        }

        while(i != m_tail)
        {
            if(positions[i] == pos)
            {
                return true;
            }

            i -= 1;

            if(i < 0)
                i = MAX_LENGTH - 1;
        }

        return false;
    }
    void deathAnimation()
    {
        int i = m_head;

        while(i != m_tail)
        {
            delay(250);
            m_renderEngine->OnErase(positions[i]); 

            i -= 1;

            if(i < 0)
                i = MAX_LENGTH - 1;
        }
        
        delay(250);

        m_renderEngine->OnErase(positions[m_tail]);

        delay(10000);
    }

private:
    int wrapPos(int coordinate, int dimension) const
    {
        if(coordinate < 0)
        {
            return dimension - 1;
        }

        if(coordinate >= dimension)
        {
            return 0;
        }

        return coordinate;
    }

    RenderEngine* m_renderEngine;

    int m_length {0};
    int m_head{0};
    int m_tail{0};
    
    const Vector2 m_dimensions{}; 
    bool m_wrapped{};

    Vector2 m_currentDirection{};

    Vector2 positions[MAX_LENGTH];

    
};



class SnakeGame
{
public:
    SnakeGame(const Vector2& dimensions, uint16_t tickMsTime, bool wrapped)
        : m_dimensions { dimensions }
        , m_snake {&m_renderEngine, dimensions, true}
        , m_tickTime {tickMsTime}
        , m_wrapped {wrapped}
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
        do
        {
            randomSeed(analogRead(0));
            m_fruitPos = Vector2{random(0, m_dimensions.x),random(0, m_dimensions.y)};
            
        } while(m_snake.isOccupied(m_fruitPos));
        
        m_renderEngine.OnDraw(m_fruitPos);
    }

    void gameLoop()
    {
        if(millis() >= lastTick + m_tickTime)
        {
            lastTick = millis();

            

            if(m_snake.getNextPosition() == m_fruitPos)
            {
                m_snake.tick(true);
                
                m_renderEngine.OnCollectFruit(m_fruitPos);

                GenerateFruit();
            }
            else if(m_snake.isOccupied(m_snake.getNextPosition()) || !IsInBounds(m_snake.getNextPosition()))
            {
                m_renderEngine.OnErase(m_fruitPos);

                m_snake.deathAnimation();
            }
            else
            {
                m_snake.tick(false);
            }
        }        
    }

private:

    bool IsInBounds(const Vector2& pos)
    {
        return (pos.x >= 0 && pos.x < m_dimensions.x) && (pos.y >= 0 && pos.y < m_dimensions.y);
    }

    #pragma region Timing
    uint16_t m_tickTime{};
    unsigned long lastTick{};
    #pragma endregion

    #pragma region Snake Game
    Snake m_snake;

    Vector2 m_dimensions{};

    RenderEngine m_renderEngine{};

    Vector2 m_fruitPos;

    bool m_wrapped;
    #pragma endregion
};

