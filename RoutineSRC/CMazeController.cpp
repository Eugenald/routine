#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include "CMazeController.h"

CMazeController::CMazeController(QWidget* widget, const Vector2D& size)
   : mMazeModel(size.x, size.y)
   , mWidget(std::make_shared<QWidget*>(widget))
   , mVisualizer(*this)
   , mDebugger(nullptr)
{
   mVisualizer.prepareWidgets(size.x, size.y);
   mKeyEventHandler = std::bind(&CMazeController::processKeyinput, this, std::placeholders::_1);

}

const CMazeModel& CMazeController::getMazeModel()
{
   return mMazeModel;
}

void CMazeController::initialize(const Vector2D& startPoint, const Vector2D& finish)
{
   mMazeModel.initialize(startPoint, finish);
}

const Vector2D& CMazeController::getStartPoint() const
{
   return mMazeModel.getStartPoint();
}

const Vector2D& CMazeController::getEndPoint() const
{
   return mMazeModel.getEndPoint();
}

void CMazeController::setDebuggerInfo(const QString& text)
{
   mDebugger->setText(text);
}

void CMazeController::processMazeCellClick(const int x, const int y)
{
   const Vector2D cell = calculateCellByCoordinate(Vector2D(x, y));
   qDebug() << "CMazeController::processMazeCellClick" << cell.x << " " << cell.y;

   if (cell != getStartPoint() && cell != getEndPoint())
   {
      mMazeModel.getCellContent(cell) == OBSTACLE_SYMBOL ? mMazeModel.setCellContent(cell, DEFAULT_SYMBOL) : mMazeModel.setCellContent(cell, OBSTACLE_SYMBOL);
      draw();
   }
}

void CMazeController::processKeyinput(QKeyEvent* event)
{
   switch (event->key())
   {
      case Qt::Key_Left:
      {
         auto prevSolution = mMazeModel.getPreviousSolution();
         if (prevSolution)
         {
            mVisualizer.draw(*mWidget, *prevSolution);
            mDebugger->setText(mMazeModel.getDebugInfoOnCurrentStep());
         }
         break;
      }
      case Qt::Key_Right:
      {
         auto nextSolution = mMazeModel.getNextSolution();
         if (nextSolution)
         {
            mVisualizer.draw(*mWidget, *nextSolution);
            mDebugger->setText(mMazeModel.getDebugInfoOnCurrentStep());
         }
         break;
      }
      case Qt::Key_Up:
         mMazeModel.restart();
         mVisualizer.draw(*mWidget);
         break;
      case Qt::Key_Down:
         mMazeModel.solve();
         mVisualizer.draw(*mWidget);
         break;
      default:
         break;
   }
}

const Vector2D CMazeController::calculateCellByCoordinate(const Vector2D& point) const
{
   const uint16_t cellSize = mVisualizer.getCellSize() + mVisualizer.getCellMargin();
   const uint16_t x = static_cast<uint16_t>(point.x / cellSize);
   const uint16_t y = static_cast<uint16_t>(point.y / cellSize);

   return Vector2D(x, y);
}

void CMazeController::draw()
{
   mVisualizer.draw(*mWidget);
}

void CMazeController::solve()
{
   mMazeModel.solve();
}

void CMazeController::setDebugInfoPlaceholder(QTextEdit* textWidget)
{
   mDebugger = new CMazeDebugger(textWidget);
}

std::function<void(QKeyEvent*)> CMazeController::getKeyEventHandler() const
{
   return mKeyEventHandler;
}
