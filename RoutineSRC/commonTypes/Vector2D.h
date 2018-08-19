#pragma once

#include <iostream>
#include <QString>

class Vector2D
{
public:
   Vector2D() : x(0), y(0) {}
   Vector2D(const int16_t vx, const int16_t vy) : x(vx), y(vy) {}
   QString toString() const
   {
      return QString(QString("Vector2D(x=") + QString::number(x) + QString(", y=") + QString::number(y) + QString(")"));
   }
   Vector2D& operator+=(const Vector2D& v) { x += v.x; y += v.y; return *this; }
   Vector2D& operator-=(const Vector2D& v) { x -= v.x; y -= v.y; return *this; }
   Vector2D& operator*=(const Vector2D& v) { x *= v.x; y *= v.y; return *this; }
   Vector2D& operator/=(const Vector2D& v) { x /= v.x; y /= v.y; return *this; }
   friend bool operator==(const Vector2D& left, const Vector2D& right);
   friend bool operator!=(const Vector2D& left, const Vector2D& right);

public:
   int16_t x;
   int16_t y;
};

inline std::ostream &operator<<(std::ostream &os, Vector2D const &m) {
   return os << "Vector2D(x=" << m.x << ", y=" << m.y << ")";
}

inline bool operator==(const Vector2D& left, const Vector2D& right) {
   return left.x == right.x && left.y == right.y;
}

inline bool operator!=(const Vector2D& left, const Vector2D& right) {
   return !(left == right);
}
