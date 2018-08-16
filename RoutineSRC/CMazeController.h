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
   explicit CMazeController(const CMazeController&) = delete;
   CMazeController& operator= (const CMazeController&) = delete;

   static CMazeController& getMazeController();

   void createMaze(const uint16_t  width, const uint16_t  height);
   std::shared_ptr<CMazeModel> getMazeModel();

   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   const Vector2D& getStartPoint() const;
   const Vector2D& getEndPoint() const;

   void draw(QWidget* widget);
   std::function<void(QKeyEvent*)> getKeyEventHandler() const;

private:
   CMazeController();
   ~CMazeController() = default;

   void fillMaze();
   void processKeyinput(QKeyEvent* event);

private:
   std::shared_ptr<CMazeModel> mMazeModel;
   std::shared_ptr<CMazeSolutionStorage> mMazeSolutionStorage;
   bool mInitialized;
   std::function<void(QKeyEvent*)> mKeyEventHandler;
};
