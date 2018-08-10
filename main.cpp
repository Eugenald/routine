#include "MainWindow.h"
#include "CMazeController.h"
#include "CAStarMazeSolver.h"
#include "Vector2D.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    CMazeController& maze = CMazeController::getMazeController();
    maze.createMaze(5, 5);
    maze.draw(&w);

    maze.setStartPoint(Vector2D(0, 0));
    maze.setEndPoint(Vector2D(0, 4));

    //CAStarMazeSolver solver(maze.getMazeModel());
    //solver.solve();

    return a.exec();
}
