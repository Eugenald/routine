#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include "CMazeController.h"

CMazeController::CMazeController()
   : mMazeModel(nullptr)
   , mInitialized(false)
{
    mKeyEventHandler = std::bind(&CMazeController::processKeyinput, this, std::placeholders::_1);
}

CMazeController& CMazeController::getMazeController()
{
   static CMazeController instance;
   return instance;
}

void CMazeController::createMaze(const uint16_t  width, const uint16_t  height)
{
   mMazeSolutionStorage = std::make_shared<CMazeSolutionStorage>(width + height);
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
   for (uint8_t y = 0; y < mMazeModel->getHeight(); y++)
   {
      for (uint8_t x = 0; x < mMazeModel->getWidth(); x++)
      {
         mMazeModel->setCellContent(Vector2D(x,y), PATH_SYMBOL);
      }
   }
}

void CMazeController::processKeyinput(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            break;
        case Qt::Key_Right:
            break;
        default:
            break;
    }
}

void CMazeController::draw(QWidget* widget)
{
   CMazeVisualizer::getVizualizer().draw(widget);
}

std::function<void(QKeyEvent*)> CMazeController::getKeyEventHandler() const
{
    return mKeyEventHandler;
}
