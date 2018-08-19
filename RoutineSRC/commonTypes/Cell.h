#pragma once

#include "Vector2D.h"

const char DEFAULT_SYMBOL = '0';
const char GOAL_SYMBOL = '1';
const char START_SYMBOL = '*';
const char DIR_UP_SYMBOL = 'u';
const char DIR_DOWN_SYMBOL = 'd';
const char DIR_LEFT_SYMBOL = 'l';
const char DIR_RIGHT_SYMBOL = 'r';
const char DIR_UP_RES_SYMBOL = 'U';
const char DIR_DOWN_RES_SYMBOL = 'D';
const char DIR_LEFT_RES_SYMBOL = 'L';
const char DIR_RIGHT_RES_SYMBOL = 'R';
const char OBSTACLE_SYMBOL = 'X';

struct Cell
{
   Cell(const char _content, Vector2D _coordinate) : content(_content), coordinate(_coordinate){}
   char content;
   int weight = 1;
   float heuristicCost = 0;
   float totalCost = std::numeric_limits<float>::max();
   bool processed = false;
   Cell* cameFrom = nullptr;
   Vector2D coordinate = Vector2D(0, 0);

   friend bool operator==(Cell& left, Cell& right);
   friend bool operator==(const Cell& left, const Cell& right);
};

inline bool operator==(Cell& left, Cell& right) {
   return left.coordinate == right.coordinate;
}

inline bool operator==(const Cell& left, const Cell& right) {
   return left.coordinate == right.coordinate;
}

inline bool operator != (Cell& left, Cell& right)
{
   return !(left == right);
}
