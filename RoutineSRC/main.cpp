#include "widgets/MainWindow.h"
#include "CMazeController.h"
#include "CAStarMazeSolver.h"
#include "Vector2D.h"
#include <QApplication>



int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow w;
   CMazeController maze(&w);

   w.setKeyEventCallback(maze.getKeyEventHandler());

   maze.createMaze(21, 21);

   maze.setStartPoint(Vector2D(0, 0));
   maze.setEndPoint(Vector2D(15, 17));
   maze.setObstacles( {Vector2D(4, 4) , Vector2D(4, 4), Vector2D(4, 5), Vector2D(4, 6), Vector2D(4, 7), Vector2D(4, 8), Vector2D(4, 9), Vector2D(4, 10), Vector2D(4, 11), Vector2D(4, 12), Vector2D(4, 13), Vector2D(3, 13), Vector2D(2, 13), Vector2D(1, 13)} );


   CAStarMazeSolver solver(maze);
   solver.setAlgorithmIterationCallback(maze.getAlgorithmIterationCallback());
   solver.solve();

   maze.draw();

   return a.exec();
}
