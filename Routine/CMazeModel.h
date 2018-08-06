#pragma once

#include <vector>
#include "Vector2D.h"

class CMazeModel
{
public:
   struct Cell
   {
      Cell(const char _content) : content(_content), heuristicCost(0), totalCost(0), cameFrom(nullptr) {};
      char content;
      const int weight = 1;
      int heuristicCost;
      int totalCost;
      Cell* cameFrom;
   };

   CMazeModel(const int _width, const int _height);

   int getWidth();
   int getHeight();
   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   Vector2D& getStartPoint();
   Vector2D& getEndPoint();
   void setCellContent(const Vector2D& cell, const char content);
   char getCellContent(const Vector2D& cell);

private:
   inline int getIndex(const Vector2D& point);

private:
   int mWidth;
   int mHeight;
   std::vector<Cell> mCellArray;
   Vector2D mStartPoint;
   Vector2D mEndPoint;
};

int CMazeModel::getIndex(const Vector2D& point)
{
   return point.x + point.y * mWidth;
}
