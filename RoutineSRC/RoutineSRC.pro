#-------------------------------------------------
#
# Project created by QtCreator 2018-08-13T19:57:31
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = RoutineSRC
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
    CAStarMazeSolver.cpp \
    CMazeController.cpp \
    CMazeVisualizer.cpp \
    mazeModel\CMazeModel.cpp \
    mazeModel\CMazeSolutionStorage.cpp \
    widgets\MainWindow.cpp \
    widgets\MazeLabel.cpp

HEADERS += \
    CAStarMazeSolver.h \
    CMazeController.h \
    CMazeVisualizer.h \
    mazeModel\CMazeModel.h \
    mazeModel\CMazeSolutionStorage.h \
    widgets\MainWindow.h \ 
    widgets\MazeLabel.h \
    commonTypes\Vector2D.h \
    commonTypes\Cell.h

FORMS += \
        mainwindow.ui

DISTFILES +=

RESOURCES += \
    image.qrc
