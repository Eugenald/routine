#pragma once

#include "Vector2D.h"

const char DEFAULT_SYMBOL = '0';
const char GOAL_SYMBOL = '1';
const char START_SYMBOL = '*';
const char DIR_UP_SYMBOL = 'u';
const char DIR_DOWN_SYMBOL = 'd';
const char DIR_LEFT_SYMBOL = 'l';
const char DIR_RIGHT_SYMBOL = 'r';
const char RESULT_UP_SYMBOL = 'U';
const char RESULT_DOWN_SYMBOL = 'D';
const char RESULT_LEFT_SYMBOL = 'L';
const char RESULT_RIGHT_SYMBOL = 'R';
const char PROCESSING_UP_SYMBOL = 'q';
const char PROCESSING_DOWN_SYMBOL = 'w';
const char PROCESSING_LEFT_SYMBOL = 'e';
const char PROCESSING_RIGHT_SYMBOL = 't';
const char OBSTACLE_SYMBOL = 'X';

struct Cell
{
   Cell(const char _content, Vector2D _coordinate) : content(_content), coordinate(_coordinate){}
   void clear()
   {
      content = DEFAULT_SYMBOL;
      heuristicCost = 0;
      totalCost = std::numeric_limits<float>::max();
      processed = false;
      cameFrom = nullptr;
   }

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

inline bool operator==(const Cell& left, const Cell& right) {
   return left.coordinate == right.coordinate;
}

inline bool operator != (const Cell& left, const Cell& right)
{
   return !(left == right);
}
