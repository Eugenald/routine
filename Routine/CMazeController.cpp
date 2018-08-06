#include "CMazeController.h"
#include <iostream>

CMazeController::CMazeController()
   : mMazeModel(nullptr)
{
}

CMazeController& CMazeController::getMazeController()
{
   static CMazeController instance;
   return instance;
}

void CMazeController::createMaze(const int width, const int height)
{
   mMazeModel = std::make_shared<CMazeModel>(width, height);
   fillMaze();
}

std::shared_ptr<CMazeModel> CMazeController::getMazeModel()
{
   return mMazeModel;
}

void CMazeController::setStartPoint(const Vector2D& point)
{
   mMazeModel->setStartPoint(point);
}

void CMazeController::setEndPoint(const Vector2D& point)
{
   mMazeModel->setEndPoint(point);
}

Vector2D& CMazeController::getStartPoint()
{
   return mMazeModel->getStartPoint();
}

Vector2D& CMazeController::getEndPoint()
{
   return mMazeModel->getEndPoint();
}

void CMazeController::fillMaze()
{
   for (int y = 0; y < mMazeModel->getHeight(); y++)
   {
      for (int x = 0; x < mMazeModel->getWidth(); x++)
      {
         mMazeModel->setCellContent(Vector2D(x,y), PATH_SYMBOL);
      }
   }
}

void CMazeController::draw()
{
   CMazeVisualizer::getVizualizer().draw();
}