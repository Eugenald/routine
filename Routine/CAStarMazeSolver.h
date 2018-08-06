#pragma once

#include <memory>
#include "CMazeController.h"

class CAStarMazeSolver
{
public:
   CAStarMazeSolver(std::shared_ptr<CMazeModel> maze);
   ~CAStarMazeSolver() = default;

   void solve();

private:
   CAStarMazeSolver() = default;

   float calculateDistance(const Vector2D& start, const Vector2D& end);
   Cell* sortAndGetNearestNode(std::vector<Cell>* array);

private:
   std::shared_ptr<CMazeModel> mMaze;
};
