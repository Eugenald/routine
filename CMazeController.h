#pragma once

#include <memory>
#include "Vector2D.h"
#include "CMazeModel.h"
#include "CMazeVisualizer.h"

class QWidget;

class CMazeController
{
public:
   CMazeController(const CMazeController&) = delete;
   CMazeController& operator= (const CMazeController&) = delete;

   static CMazeController& getMazeController();

   void createMaze(const int width, const int height);
   std::shared_ptr<CMazeModel> getMazeModel();

   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   const Vector2D& getStartPoint() const;
   const Vector2D& getEndPoint() const;

   void draw(QWidget* widget);

private:
   CMazeController();
   ~CMazeController() = default;

   void fillMaze();


private:
   std::shared_ptr<CMazeModel> mMazeModel;
};
