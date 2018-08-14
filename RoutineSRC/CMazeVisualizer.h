#pragma once

#include <QWidget>

class QLabel;

enum class Texture: char{ DEFAULT, GOAL, START, UP, DOWN, LEFT, RIGHT, UP_RES, DOWN_RES, LEFT_RES, RIGHT_RES };

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
   QVector<std::tuple<Texture, QPixmap, QString, char>> mTextures;

   QVector<QLabel*> mLabelArray;
};
