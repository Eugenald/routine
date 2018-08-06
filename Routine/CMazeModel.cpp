#include <iostream>
#include "CMazeModel.h"

CMazeModel::CMazeModel(const int _width, const int _height)
   : mWidth(_width)
   , mHeight(_height)
{
   mCellArray.reserve(mWidth*mHeight);
   for (int i = 0; i < mWidth*mHeight; i++)
   {
      mCellArray.push_back('-');
   }
}

int CMazeModel::getWidth()
{
   return mWidth;
}

int CMazeModel::getHeight()
{
   return mHeight;
}

void CMazeModel::setCellContent(const Vector2D& cell, const char content)
{
   mCellArray[getIndex(cell)].content = content;
}

char CMazeModel::getCellContent(const Vector2D& cell)
{
   return mCellArray[getIndex(cell)].content;
}

void CMazeModel::setStartPoint(const Vector2D& point)
{
   mStartPoint = point;
   mCellArray[getIndex(mStartPoint)].content = '*';
   std::cout << "CMazeModel::setStartPoint X = " << mStartPoint.x << " Y = " << mStartPoint.y << std::endl;
   std::cout << "CMazeModel::setStartPoint index = " << getIndex(mStartPoint) << std::endl;
}

void CMazeModel::setEndPoint(const Vector2D& point)
{
   mEndPoint = point;
   mCellArray[getIndex(mEndPoint)].content = '1';
   std::cout << "CMazeModel::setStartPoint X = " << mEndPoint.x << " Y = " << mEndPoint.y << std::endl;
   std::cout << "CMazeModel::setStartPoint index = " << getIndex(mEndPoint) << std::endl;
}

Vector2D& CMazeModel::getStartPoint()
{
   return mStartPoint;
}

Vector2D& CMazeModel::getEndPoint()
{
   return mEndPoint;
}
