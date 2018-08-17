#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include "CMazeController.h"

CMazeController::CMazeController(QWidget* widget)
   : mMazeModel(nullptr)
   , mInitialized(false)
   , mWidget(std::make_shared<QWidget*>(widget))
   , mAlgorithmSteps(0)
   , mVisualizer(*this)
{
    mKeyEventHandler = std::bind(&CMazeController::processKeyinput, this, std::placeholders::_1);
    mAlgorithmIterationCallback =  std::bind(&CMazeController::processAlgorithmIteration, this);
}

void CMazeController::createMaze(const uint16_t  width, const uint16_t  height)
{
   mMazeSolutionStorage = std::make_shared<CMazeSolutionStorage>(width + height);
   mMazeModel = std::make_shared<CMazeModel>(width, height);
   fillMaze();
   mVisualizer.prepareWidgets(width, height);
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
            if ((mAlgorithmSteps - 1) >= 0 && (mAlgorithmSteps - 1) < mMazeSolutionStorage->getStorageSize())
            {
                mAlgorithmSteps--;
                mVisualizer.draw(*mWidget, mMazeSolutionStorage->getModelAt(mAlgorithmSteps));
            }
            break;
        case Qt::Key_Right:
            if ((mAlgorithmSteps + 1) >= 0 && (mAlgorithmSteps + 1) < mMazeSolutionStorage->getStorageSize())
            {
                mAlgorithmSteps++;
                mVisualizer.draw(*mWidget, mMazeSolutionStorage->getModelAt(mAlgorithmSteps));
            }
            break;
        case Qt::Key_Up:
            mAlgorithmSteps = 0;
            mVisualizer.draw(*mWidget, mMazeSolutionStorage->getModelAt(mAlgorithmSteps));
            break;
        default:
            break;
    }
}

void CMazeController::processAlgorithmIteration()
{
    mMazeSolutionStorage->pushBackModel(*mMazeModel);
    qDebug() << "CMazeController::processAlgorithmIteration() storageSize=" << mMazeSolutionStorage->getStorageSize();
}

void CMazeController::draw()
{
   mVisualizer.draw(*mWidget);
}

std::function<void(QKeyEvent*)> CMazeController::getKeyEventHandler() const
{
    return mKeyEventHandler;
}

std::function<void()>& CMazeController::getAlgorithmIterationCallback()
{
    return mAlgorithmIterationCallback;
}
