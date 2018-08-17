#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

   void setKeyEventCallback(const std::function<void(QKeyEvent*)>& function);

protected:
   virtual void keyPressEvent(QKeyEvent* event);

private:
   Ui::MainWindow *ui;
   std::function<void(QKeyEvent*)> mKeyInputCallback;
};

#endif // MAINWINDOW_H
