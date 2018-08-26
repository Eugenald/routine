#pragma once

#include <QWidget>
#include <memory>
#include <widgets/MazeLabel.h>

class QLabel;
class CMazeController;
struct Cell;

enum class Texture: char{ DEFAULT, GOAL, START, OBSTACLE,
                          UP, DOWN, LEFT, RIGHT,
                          UP_RES, DOWN_RES, LEFT_RES, RIGHT_RES,
                          UP_PROC, DOWN_PROC, LEFT_PROC, RIGHT_PROC };

class CMazeVisualizer : public QObject
{
public:
   explicit CMazeVisualizer(CMazeController& mazeCtrl);
   ~CMazeVisualizer() = default;
   CMazeVisualizer(const CMazeVisualizer&) = delete;
   CMazeVisualizer& operator= (const CMazeVisualizer&) = delete;

   void prepareWidgets(const uint8_t width, const uint8_t height);
   void draw(QWidget* widget) const;
   void draw(QWidget* widget, const std::vector<Cell>&) const;

   uint16_t getCellSize() const;
   uint16_t getCellMargin() const;

public:
   void triggerClick(const int x, const int y);

private:
   CMazeController& mMazeCtrl;
   QPixmap mDefaultTexture;
   QVector<std::tuple<Texture, QPixmap, QString, char>> mCellTextures;
   QVector<std::tuple<QPixmap, QString, int>> mNumberTextures;
   std::vector<std::unique_ptr<MazeLabel>> mCellLabelArray;
   std::vector<std::unique_ptr<MazeLabel>> mNumberLabelArray;
};
