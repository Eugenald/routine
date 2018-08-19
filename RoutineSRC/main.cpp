#include "widgets/MainWindow.h"
#include "CMazeController.h"
#include "commonTypes\Vector2D.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow mainWindow;

   CMazeController maze(&mainWindow, Vector2D(21, 21));

   mainWindow.setKeyEventCallback(maze.getKeyEventHandler());

   maze.initialize(Vector2D(0, 0), Vector2D(15, 17));
   maze.setDebugInfoPlaceholder(mainWindow.getTextBrowser());
   maze.solve();
   maze.draw();

   return a.exec();
}
