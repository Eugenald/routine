#include <iostream>
#include <QDebug>
#include "CMazeModel.h"

CMazeModel::CMazeModel(const uint8_t _width, const uint8_t _height)
   : mWidth(_width)
   , mHeight(_height)
   , mStartPoint()
   , mEndPoint()
   , mStartPointIsSet(false)
   , mEndPointIsSet(false)
   , mMazeSolver(*this)
   , mMazeSolutionStorage(_width + _height)
{
   mCellArray.reserve(mWidth*mHeight);

   for (uint8_t y = 0; y < mHeight; y++)
   {
      for (uint8_t x = 0; x < mWidth; x++)
      {
         mCellArray.push_back(Cell(DEFAULT_SYMBOL, Vector2D(x, y)));
      }
   }

   mAlgoIterationCallback =  std::bind(&CMazeModel::processAlgorithmIteration, this);
}

void CMazeModel::initialize(const Vector2D& startPoint, const Vector2D& finish)
{
   setStartPoint(startPoint);
   setEndPoint(finish);

   mMazeSolver.setAlgorithmIterationCallback(mAlgoIterationCallback);
}

void CMazeModel::solve()
{
   if (isEndPointSet() && isStartPointSet())
   {
      mMazeSolver.solve();
   }
   else
   {
      std::cout << "START or END point is not set " << std::endl;
   }
}

void CMazeModel::processAlgorithmIteration()
{
   mMazeSolutionStorage.pushBackModelData(getMazeData());
   qDebug() << "CMazeModel::processAlgorithmIteration() storageSize=" << mMazeSolutionStorage.getStorageSize();
}

void CMazeModel::setStartPoint(const Vector2D& point)
{
   mStartPoint = point;
   const uint16_t index = getIndex(mStartPoint);

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
   const uint16_t index = getIndex(mEndPoint);

   if (mCellArray.size() > index)
   {
      mEndPointIsSet = true;
      mCellArray[index].content = GOAL_SYMBOL;
      std::cout << "CMazeModel::setEndPoint X = " << mEndPoint.x << " Y = " << mEndPoint.y << std::endl;
      std::cout << "CMazeModel::setEndPoint index = " << getIndex(mEndPoint) << std::endl;
   }
   else
   {
      std::cout << "EndPoint out of range" << std::endl;
   }
}
