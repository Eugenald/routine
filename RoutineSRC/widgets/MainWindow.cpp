#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   setFocusPolicy(Qt::StrongFocus);
   ui->setupUi(this);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::setKeyEventCallback(const std::function<void(QKeyEvent*)>& function)
{
   mKeyInputCallback = function;
}

QTextEdit* MainWindow::getTextBrowser()
{
   return ui->textBrowser;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
   mKeyInputCallback(event);
}
