#include <QWidget>
#include <iostream>
#include "CMazeController.h"

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
   CMazeVisualizer::getVizualizer().prepareWidgets(width, height);
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

const Vector2D& CMazeController::getStartPoint() const
{
   return mMazeModel->getStartPoint();
}

const Vector2D& CMazeController::getEndPoint() const
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

void CMazeController::draw(QWidget* widget)
{
   CMazeVisualizer::getVizualizer().draw(widget);
}
