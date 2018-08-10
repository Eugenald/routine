#pragma once

#include <QWidget>

class QLabel;

class CMazeVisualizer
{
public:
   CMazeVisualizer(const CMazeVisualizer&) = delete;
   CMazeVisualizer& operator= (const CMazeVisualizer&) = delete;

   static CMazeVisualizer& getVizualizer();
   void prepareWidgets(const int width, const int height);
   void draw(QWidget* widget);

private:
   CMazeVisualizer();
   ~CMazeVisualizer() = default;

   QPixmap mDefaultTexture;

   QVector<QLabel*> mLabelArray;
};
