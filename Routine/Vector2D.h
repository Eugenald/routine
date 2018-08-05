#pragma once

class Vector2D
{
public:
   Vector2D() : x(0), y(0) {}
   Vector2D(const int vx, const int vy) : x(vx), y(vy) {}
   Vector2D& operator+=(const Vector2D& v) { x += v.x; y += v.y; return *this; }
   Vector2D& operator-=(const Vector2D& v) { x -= v.x; y -= v.y; return *this; }
   Vector2D& operator*=(const Vector2D& v) { x *= v.x; y *= v.y; return *this; }
   Vector2D& operator/=(const Vector2D& v) { x /= v.x; y /= v.y; return *this; }

public:
   int x;
   int y;
};