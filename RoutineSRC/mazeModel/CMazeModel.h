#pragma once

#include <vector>
#include <functional>
#include "commonTypes\Vector2D.h"
#include "commonTypes\Cell.h"
#include "CAStarMazeSolver.h"
#include "CMazeSolutionStorage.h"

class CMazeModel
{
public:
   explicit CMazeModel(const uint8_t _width, const uint8_t _height);

   void initialize(const Vector2D& startPoint, const Vector2D& finish);
   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   void solve();
   void restart();
   const std::vector<Cell>* getNextSolution();
   const std::vector<Cell>* getPreviousSolution();
   QString getDebugInfoOnCurrentStep() const;

   inline uint16_t getWidth() const;
   inline uint16_t getHeight() const;
   inline const Vector2D& getStartPoint() const;
   inline const Vector2D& getEndPoint() const;
   inline bool isStartPointSet() const;
   inline bool isEndPointSet() const;
   inline void setCellContent(const Vector2D& cell, const char content);
   inline char getCellContent(const Vector2D& cell) const;
   inline Cell* getCell(const Vector2D& point);
   inline const std::vector<Cell>& getMazeData() const;
   inline uint16_t getIndex(const Vector2D& point) const;
   inline const CMazeSolutionStorage& getSolutions() const;

private:
   void processAlgorithmIteration(const std::vector<Cell*>& vec);

private:
   uint8_t mWidth;
   uint8_t mHeight;
   std::vector<Cell> mCellArray;
   Vector2D mStartPoint;
   Vector2D mEndPoint;

   bool mStartPointIsSet;
   bool mEndPointIsSet;
   CAStarMazeSolver mMazeSolver;
   CMazeSolutionStorage mMazeSolutionStorage;
   uint32_t mAlgorithmSteps;
   std::function<void(std::vector<Cell*>)> mAlgoIterationCallback;
};

uint16_t CMazeModel::getWidth() const
{
   return mWidth;
}

uint16_t CMazeModel::getHeight() const
{
   return mHeight;
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

char CMazeModel::getCellContent(const Vector2D& cell) const
{
   return mCellArray[getIndex(cell)].content;
}

void CMazeModel::setCellContent(const Vector2D& cell, const char content)
{
   mCellArray[getIndex(cell)].content = content;
}

Cell* CMazeModel::getCell(const Vector2D& point)
{
   return (getIndex(point) < mCellArray.size() && point.x >= 0 && point.y >= 0) ? &mCellArray[getIndex(point)] : nullptr;
}

const std::vector<Cell>& CMazeModel::getMazeData() const
{
   return mCellArray;
}

uint16_t CMazeModel::getIndex(const Vector2D& point) const
{
   return point.x + point.y * mWidth;
}

const CMazeSolutionStorage& CMazeModel::getSolutions() const
{
   return mMazeSolutionStorage;
}
