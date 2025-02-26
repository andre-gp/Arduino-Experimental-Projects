#include "vector2.h"

#define FUNC_DRAW_MACRO(OnEvent) bool (*OnEvent) (Vector2 pos)

class Snake
{
public:
    Snake()
    {
        
    }

    Snake(const Vector2& headPosition) 
    : m_headPosition{ headPosition }
    {
        
    }
private:
    Vector2 m_headPosition;
};



class SnakeGame
{
public:
    SnakeGame(const Vector2& dimensions)
        : m_dimensions { dimensions }
        , m_snake {dimensions / 2}
    {

    }
    
    void BindFunctions(FUNC_DRAW_MACRO(onDraw), FUNC_DRAW_MACRO(onErase))
    {
        /* Bind the functions of drawing and erasing to screen */
        m_onDraw = onDraw;
        m_onErase = onErase;
    }



private:

    #pragma region Functions
    void draw(Vector2 pos);
    #pragma endregion

    #pragma region Variables
    Vector2 m_dimensions{};

    Snake m_snake;

    FUNC_DRAW_MACRO(m_onDraw);
    FUNC_DRAW_MACRO(m_onErase);
    #pragma endregion
};

