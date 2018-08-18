#pragma once

#include <memory>
#include <functional>
#include "Vector2D.h"
#include "CMazeModel.h"
#include "CMazeVisualizer.h"
#include "CMazeSolutionStorage.h"

class QWidget;

class CMazeController
{
public:
   explicit CMazeController(QWidget* widget);
   ~CMazeController() = default;
   CMazeController(const CMazeController&) = delete;
   CMazeController& operator= (const CMazeController&) = delete;

   void createMaze(const uint16_t  width, const uint16_t  height);
   std::shared_ptr<CMazeModel> getMazeModel();

   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   const Vector2D& getStartPoint() const;
   const Vector2D& getEndPoint() const;
   void setObstacles(const std::vector<Vector2D>& cells);

   void processMazeCellClick(const int x, const int y);

   void draw();
   std::function<void(QKeyEvent*)> getKeyEventHandler() const;
   std::function<void()>& getAlgorithmIterationCallback();

private:
   void fillMaze();
   void processKeyinput(QKeyEvent* event);
   void processAlgorithmIteration();
   const Vector2D calculateCellByCoordinate(const Vector2D& point) const;

private:
   std::shared_ptr<CMazeModel> mMazeModel;
   std::shared_ptr<CMazeSolutionStorage> mMazeSolutionStorage;
   std::shared_ptr<QWidget*> mWidget;
   bool mInitialized;
   uint32_t mAlgorithmSteps;
   std::function<void(QKeyEvent*)> mKeyEventHandler;
   std::function<void()> mAlgorithmIterationCallback;
   CMazeVisualizer mVisualizer;
};
