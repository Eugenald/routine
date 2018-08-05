#include <iostream>
#include "CVisualizer.h"
#include "CMazeCreator.h"
#include "Vector2D.h"

int main()
{
   CVisualizer& viz = CVisualizer::getVizualizer();
   CMazeCreator& maze = CMazeCreator::getMazeCreator(20, 10);
   viz.draw(maze.getMaze());

   maze.setStartPoint(Vector2D(5, 5));

   viz.draw(maze.getMaze());

   system("pause");
}