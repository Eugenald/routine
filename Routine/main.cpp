#include <iostream>
#include "CMazeController.h"
#include "CAStarMazeSolver.h"
#include "Vector2D.h"

int main()
{
   CMazeController& maze = CMazeController::getMazeController();
   maze.createMaze(21, 10);
   maze.draw();

   maze.setStartPoint(Vector2D(0, 0));
   maze.setEndPoint(Vector2D(20, 9));

   maze.draw();

   CAStarMazeSolver solver(maze.getMazeModel());
   solver.solve();

   std::vector<Cell*> vec{ nullptr, nullptr };
   std::cout << vec.size();

   system("pause");
}