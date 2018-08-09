#include <iostream>
#include "CMazeModel.h"

CMazeModel::CMazeModel(const int _width, const int _height)
   : mWidth(_width)
   , mHeight(_height)
   , mStartPoint()
   , mEndPoint()
   , mStartPointIsSet(false)
   , mEndPointIsSet(false)
{
   mCellArray.reserve(mWidth*mHeight);

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         mCellArray.push_back(Cell('-', Vector2D(x, y)));
      }
   }
}

int CMazeModel::getWidth() const
{
   return mWidth;
}

int CMazeModel::getHeight() const
{
   return mHeight;
}

void CMazeModel::setCellContent(const Vector2D& cell, const char content)
{
   mCellArray[getIndex(cell)].content = content;
}

char CMazeModel::getCellContent(const Vector2D& cell) const
{
   return mCellArray[getIndex(cell)].content;
}

Cell* CMazeModel::getCell(const Vector2D& point)
{
   return (getIndex(point) < mCellArray.size() && point.x >= 0 && point.y >= 0) ? &mCellArray[getIndex(point)] : nullptr;
}

void CMazeModel::setStartPoint(const Vector2D& point)
{
   mStartPoint = point;
   const int index = getIndex(mStartPoint);

   if (mCellArray.size() > index)
   {
      mStartPointIsSet = true;
      mCellArray[index].content = START_SYMBOL;
      mCellArray[index].weight = 0;
      std::cout << "CMazeModel::setStartPoint X = " << mStartPoint.x << " Y = " << mStartPoint.y << std::endl;
      std::cout << "CMazeModel::setStartPoint index = " << index << std::endl;
   }
   else
   {
      std::cout << "StartPoint out of range" << std::endl;
   }
}

void CMazeModel::setEndPoint(const Vector2D& point)
{
   mEndPoint = point;
   const int index = getIndex(mEndPoint);

   if (mCellArray.size() > index)
   {
      mEndPointIsSet = true;
      mCellArray[getIndex(mEndPoint)].content = GOAL_SYMBOL;
      std::cout << "CMazeModel::setEndPoint X = " << mEndPoint.x << " Y = " << mEndPoint.y << std::endl;
      std::cout << "CMazeModel::setEndPoint index = " << getIndex(mEndPoint) << std::endl;
   }
   else
   {
      std::cout << "EndPoint out of range" << std::endl;
   }
}

const Vector2D& CMazeModel::getStartPoint() const
{
   return mStartPoint;
}

const Vector2D& CMazeModel::getEndPoint() const
{
   return mEndPoint;
}

bool CMazeModel::isStartPointSet() const
{
   return mStartPointIsSet;
}

bool CMazeModel::isEndPointSet() const
{
   return mEndPointIsSet;
}