#include <iostream>
#include <QDebug>
#include "CMazeModel.h"

CMazeModel::CMazeModel(const uint8_t _width, const uint8_t _height)
   : mWidth(_width)
   , mHeight(_height)
   , mCellArray()
   , mStartPoint()
   , mEndPoint()
   , mStartPointIsSet(false)
   , mEndPointIsSet(false)
   , mMazeSolver(*this)
   , mMazeSolutionStorage(_width + _height)
   , mAlgorithmSteps(0)
   , mAlgoIterationCallback()
{
   mCellArray.reserve(mWidth*mHeight);

   for (uint8_t y = 0; y < mHeight; y++)
   {
      for (uint8_t x = 0; x < mWidth; x++)
      {
         mCellArray.push_back(Cell(DEFAULT_SYMBOL, Vector2D(x, y)));
      }
   }

   mAlgoIterationCallback =  std::bind(&CMazeModel::processAlgorithmIteration, this, std::placeholders::_1);
}

void CMazeModel::initialize(const Vector2D& startPoint, const Vector2D& finish)
{
   setStartPoint(startPoint);
   setEndPoint(finish);

   mMazeSolver.setAlgorithmIterationCallback(mAlgoIterationCallback);
}

void CMazeModel::processAlgorithmIteration(const std::vector<Cell*>& vec)
{
   QString debugInfo = QString();
   for (auto i : vec)
   {
      debugInfo.append(i->coordinate.toString() + " cost=" + QString::number(i->totalCost) + "\n");
   }

   mMazeSolutionStorage.pushBackModelData(getMazeData(), std::move(debugInfo));
   mAlgorithmSteps = mMazeSolutionStorage.getStorageSize() - 1;
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
      qDebug() << "CMazeModel::setStartPoint X = " << mStartPoint.x << " Y = " << mStartPoint.y;
      qDebug() << "CMazeModel::setStartPoint index = " << index;
   }
   else
   {
      qDebug() << "StartPoint out of range";
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
      qDebug() << "CMazeModel::setEndPoint X = " << mEndPoint.x << " Y = " << mEndPoint.y;
      qDebug() << "CMazeModel::setEndPoint index = " << getIndex(mEndPoint);
   }
   else
   {
      qDebug() << "EndPoint out of range";
   }
}

void CMazeModel::solve()
{
   if (isEndPointSet() && isStartPointSet())
   {
      mMazeSolver.solve();
   }
   else
   {
      qDebug() << "START or END point is not set ";
   }
}

void CMazeModel::restart()
{
   qDebug() << "CMazeModel::restart";
   mAlgorithmSteps = 0;
   mMazeSolutionStorage.clearStorage();

   for (auto& i : mCellArray)
   {
      if (i.content != GOAL_SYMBOL && i.content != START_SYMBOL && i.content != OBSTACLE_SYMBOL)
      {
         i.clear();
      }
   }
}

const std::vector<Cell>* CMazeModel::getNextSolution()
{
   const uint32_t nextStep = mAlgorithmSteps + 1;

   if (nextStep < mMazeSolutionStorage.getStorageSize())
   {
      mAlgorithmSteps++;

      return mMazeSolutionStorage.getModelDataAt(mAlgorithmSteps);
   }
   else
   {
      return nullptr;
   }
}

const std::vector<Cell>* CMazeModel::getPreviousSolution()
{
   const uint32_t prevStep = mAlgorithmSteps - 1;

   if (prevStep < mMazeSolutionStorage.getStorageSize())
   {
      mAlgorithmSteps--;
      return mMazeSolutionStorage.getModelDataAt(mAlgorithmSteps);
   }
   else
   {
      return nullptr;
   }
}

QString CMazeModel::getDebugInfoOnCurrentStep() const
{
   return mMazeSolutionStorage.getModelDebugInfoAt(mAlgorithmSteps);
}
