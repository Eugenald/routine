#pragma once

#include <QMainWindow>
#include <QTextEdit>
#include <functional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

   void setKeyEventCallback(const std::function<void(QKeyEvent*)>& function);
   QTextEdit* getTextBrowser();

protected:
   virtual void keyPressEvent(QKeyEvent* event);

private:
   Ui::MainWindow *ui;
   std::function<void(QKeyEvent*)> mKeyInputCallback;
};
