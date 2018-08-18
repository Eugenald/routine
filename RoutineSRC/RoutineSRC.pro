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
    CMazeModel.cpp \
    CMazeVisualizer.cpp \
    widgets\MainWindow.cpp \
    CMazeSolutionStorage.cpp \
    widgets/MazeLabel.cpp

HEADERS += \
    CAStarMazeSolver.h \
    CMazeController.h \
    CMazeModel.h \
    CMazeVisualizer.h \
    Vector2D.h \
    widgets\MainWindow.h \
    CMazeSolutionStorage.h \
    widgets/MazeLabel.h

FORMS += \
        mainwindow.ui

DISTFILES +=

RESOURCES += \
    image.qrc
