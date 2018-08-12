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

    w.setKeyEventCallback(maze.getKeyEventHandler());

    maze.createMaze(21, 21);

    maze.setStartPoint(Vector2D(0, 0));
    maze.setEndPoint(Vector2D(15, 17));

    CAStarMazeSolver solver(maze.getMazeModel());
    solver.solve();

    maze.draw(&w);

    return a.exec();
}
