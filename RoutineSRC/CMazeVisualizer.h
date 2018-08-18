#pragma once

#include <QWidget>
#include <widgets/MazeLabel.h>

class QLabel;
class CMazeController;
class CMazeModel;

enum class Texture: char{ DEFAULT, GOAL, START, UP, DOWN, LEFT, RIGHT, UP_RES, DOWN_RES, LEFT_RES, RIGHT_RES };

class CMazeVisualizer : public QObject
{
public:
   explicit CMazeVisualizer(CMazeController& mazeCtrl);
   ~CMazeVisualizer() = default;
   CMazeVisualizer(const CMazeVisualizer&) = delete;
   CMazeVisualizer& operator= (const CMazeVisualizer&) = delete;

   void prepareWidgets(const int width, const int height);
   void draw(QWidget* widget) const;
   void draw(QWidget* widget, const CMazeModel* model) const;

   uint16_t getCellSize() const;
   uint16_t getCellMargin() const;

public:
   void triggerClick(const int x, const int y);

private:
   CMazeController& mMazeCtrl;
   QPixmap mDefaultTexture;
   QVector<std::tuple<Texture, QPixmap, QString, char>> mTextures;
   QVector<MazeLabel*> mLabelArray;
};
