#pragma once
#include <iostream>

class Vector2D
{
public:
   Vector2D() : x(0), y(0) {}
   Vector2D(const int vx, const int vy) : x(vx), y(vy) {}
   Vector2D& operator+=(const Vector2D& v) { x += v.x; y += v.y; return *this; }
   Vector2D& operator-=(const Vector2D& v) { x -= v.x; y -= v.y; return *this; }
   Vector2D& operator*=(const Vector2D& v) { x *= v.x; y *= v.y; return *this; }
   Vector2D& operator/=(const Vector2D& v) { x /= v.x; y /= v.y; return *this; }
   friend bool operator==(const Vector2D& left, const Vector2D& right);

public:
   int x;
   int y;
};

inline std::ostream &operator<<(std::ostream &os, Vector2D const &m) {
   return os << "Vector2D(x" << m.x << "," << m.y << ")";
}

inline bool operator==(const Vector2D& left, const Vector2D& right) {
   return left.x == right.x && left.y == right.y;
}