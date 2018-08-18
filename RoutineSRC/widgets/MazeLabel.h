#pragma once

#include <QLabel>
#include <QWidget>
#include <Qt>

class MazeLabel : public QLabel
{
   Q_OBJECT
public:
   explicit MazeLabel(QWidget* parent = nullptr);
   ~MazeLabel();

signals:
    void clicked(const int x, const int y);

protected:
    void mousePressEvent(QMouseEvent* event);
};
