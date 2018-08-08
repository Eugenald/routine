﻿#pragma once

#include <vector>
#include <limits>
#include "Vector2D.h"

const char GOAL_SYMBOL = '1';
const char START_SYMBOL = '*';
const char PATH_SYMBOL = '0';
const char DIR_UP_SYMBOL = 'U';
const char DIR_DOWN_SYMBOL = 'D';
const char DIR_LEFT_SYMBOL = 'L';
const char DIR_RIGHT_SYMBOL = 'R';

struct Cell
{
   Cell(const char _content, Vector2D _coordinate) : content(_content), coordinate(_coordinate){};
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

class CMazeModel
{
public:
   CMazeModel(const int _width, const int _height);

   int getWidth() const;
   int getHeight() const;
   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   const Vector2D& getStartPoint() const;
   const Vector2D& getEndPoint() const;
   void setCellContent(const Vector2D& cell, const char content);
   char getCellContent(const Vector2D& cell) const;
   bool isStartPointSet() const;
   bool isEndPointSet() const;

   Cell* getCell(const Vector2D& point);

private:
   inline int getIndex(const Vector2D& point) const;

private:
   int mWidth;
   int mHeight;
   std::vector<Cell> mCellArray;
   Vector2D mStartPoint;
   Vector2D mEndPoint;

   bool mStartPointIsSet;
   bool mEndPointIsSet;
};

int CMazeModel::getIndex(const Vector2D& point) const
{
   return point.x + point.y * mWidth;
}
