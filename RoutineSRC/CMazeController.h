#pragma once

#include <memory>
#include <functional>
#include "commonTypes\Vector2D.h"
#include "mazeModel\CMazeModel.h"
#include "CMazeVisualizer.h"

class QWidget;

class CMazeController
{ 
public:
   explicit CMazeController(QWidget* widget, const Vector2D& size);
   ~CMazeController() = default;
   CMazeController(const CMazeController&) = delete;
   CMazeController& operator= (const CMazeController&) = delete;
   const CMazeModel& getMazeModel();

   void initialize(const Vector2D& startPoint, const Vector2D& finish);
   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   const Vector2D& getStartPoint() const;
   const Vector2D& getEndPoint() const;
   void setObstacles(const std::vector<Vector2D>& cells);

   void processMazeCellClick(const int x, const int y);

   void draw();
   void solve();
   std::function<void(QKeyEvent*)> getKeyEventHandler() const;

private:
   void processKeyinput(QKeyEvent* event);
   const Vector2D calculateCellByCoordinate(const Vector2D& point) const;
   void processRestart();

private:
   CMazeModel mMazeModel;
   std::shared_ptr<QWidget*> mWidget;
   uint32_t mAlgorithmSteps;
   std::function<void(QKeyEvent*)> mKeyEventHandler;
   CMazeVisualizer mVisualizer;
};
