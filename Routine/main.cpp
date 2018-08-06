#include <iostream>
#include "CMazeController.h"
#include "Vector2D.h"

int main()
{
   CMazeController& maze = CMazeController::getMazeController();
   maze.createMaze(21, 11);
   maze.draw();

   maze.setStartPoint(Vector2D(5, 5));
   maze.setEndPoint(Vector2D(20, 10));

   maze.draw();

   system("pause");
}