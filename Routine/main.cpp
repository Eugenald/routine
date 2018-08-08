#include <iostream>
#include "CMazeController.h"
#include "CAStarMazeSolver.h"
#include "Vector2D.h"

int main()
{
   CMazeController& maze = CMazeController::getMazeController();
   maze.createMaze(5, 5);
   maze.draw();

   maze.setStartPoint(Vector2D(0, 0));
   maze.setEndPoint(Vector2D(4, 4));

   maze.draw();

   CAStarMazeSolver solver(maze.getMazeModel());
   solver.solve();

   maze.draw();


   system("pause");
}