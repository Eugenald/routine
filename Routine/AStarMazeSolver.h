#pragma once

#include <memory>
#include "CMazeController.h"

class CAStarMazeSolver
{

public:
   CAStarMazeSolver(const CAStarMazeSolver&) = delete;
   CAStarMazeSolver& operator= (const CAStarMazeSolver&) = delete;

   static CAStarMazeSolver& getAStarMazeSolver(const CMazeController& );

private:
   /*CAStarMazeSolver(std::shared_ptr<Maze> maze);
   CAStarMazeSolver() = default;
   ~CAStarMazeSolver() = default;

   std::shared_ptr<Maze> mMaze;*/
};
