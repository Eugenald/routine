#include <QGraphicsScene>
#include <QKeyEvent>
#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    mKeyInputCallback(event);
}
