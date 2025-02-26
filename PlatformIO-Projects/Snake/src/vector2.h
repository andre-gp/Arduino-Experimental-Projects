struct Vector2
{
    int x;
    int y;
};

Vector2 operator/(const Vector2& v, const int& num)
{
    return Vector2{v.x/num, v.y/num};
}