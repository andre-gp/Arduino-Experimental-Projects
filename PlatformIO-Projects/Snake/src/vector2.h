struct Vector2
{
    int x;
    int y;

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2{x + other.x, y + other.y};
    }

    bool operator==(const Vector2& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    void operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
    }
};

Vector2 operator/(const Vector2& v, const int& num)
{
    return Vector2{v.x/num, v.y/num};
}


