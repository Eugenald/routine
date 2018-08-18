#include "MazeLabel.h"
#include <QMouseEvent>
#include <QDebug>

MazeLabel::MazeLabel(QWidget* parent)
   : QLabel(parent)
{
}

MazeLabel::~MazeLabel()
{
}

void MazeLabel::mousePressEvent(QMouseEvent* event)
{
   emit clicked(static_cast<int>(event->windowPos().x()), static_cast<int>(event->windowPos().y()));
}
