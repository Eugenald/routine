#include <iostream>
#include <QLabel>
#include <QDebug>
#include "CMazeVisualizer.h"
#include "CMazeController.h"

#define CELLSIZE 40
#define NUMBERSIZEX 10
#define NUMBERSIZEY 20
#define MARGIN 5
const QString DEFAULT_TEXTURE = ":/images/button.png";
const QString GOAL_TEXTURE = ":/images/goal.png";
const QString START_TEXTURE = ":/images/start.png";
const QString OBSTACLE_TEXTURE = ":/images/obstacle.png";
const QString UP_TEXTURE = ":/images/up.png";
const QString DOWN_TEXTURE = ":/images/down.png";
const QString LEFT_TEXTURE = ":/images/left.png";
const QString RIGHT_TEXTURE = ":/images/right.png";
const QString UP_RES_TEXTURE = ":/images/resultUp.png";
const QString DOWN_RES_TEXTURE = ":/images/resultDown.png";
const QString LEFT_RES_TEXTURE = ":/images/resultLeft.png";
const QString RIGHT_RES_TEXTURE = ":/images/resultRight.png";
const QString UP_PROC_TEXTURE = ":/images/processingUp.png";
const QString DOWN_PROC_TEXTURE = ":/images/processingDown.png";
const QString LEFT_PROC_TEXTURE = ":/images/processingLeft.png";
const QString RIGHT_PROC_TEXTURE = ":/images/processingRight.png";

const QString NUMBER_0_TEXTURE = ":/images/0.png";
const QString NUMBER_1_TEXTURE = ":/images/1.png";
const QString NUMBER_2_TEXTURE = ":/images/2.png";
const QString NUMBER_3_TEXTURE = ":/images/3.png";
const QString NUMBER_4_TEXTURE = ":/images/4.png";
const QString NUMBER_5_TEXTURE = ":/images/5.png";
const QString NUMBER_6_TEXTURE = ":/images/6.png";
const QString NUMBER_7_TEXTURE = ":/images/7.png";
const QString NUMBER_8_TEXTURE = ":/images/8.png";
const QString NUMBER_9_TEXTURE = ":/images/9.png";


CMazeVisualizer::CMazeVisualizer(CMazeController& mazeCtrl)
   : mMazeCtrl(mazeCtrl)
   , mDefaultTexture()
   , mCellTextures()
   , mNumberTextures()
   , mCellLabelArray()
   , mNumberLabelArray()
{
   mCellTextures = { {Texture::DEFAULT, QPixmap(), DEFAULT_TEXTURE, DEFAULT_SYMBOL},
                     {Texture::GOAL, QPixmap(), GOAL_TEXTURE, GOAL_SYMBOL},
                     {Texture::START, QPixmap(), START_TEXTURE, START_SYMBOL},
                     {Texture::OBSTACLE, QPixmap(), OBSTACLE_TEXTURE, OBSTACLE_SYMBOL},
                     {Texture::UP, QPixmap(), UP_TEXTURE, DIR_UP_SYMBOL},
                     {Texture::DOWN, QPixmap(), DOWN_TEXTURE, DIR_DOWN_SYMBOL},
                     {Texture::LEFT, QPixmap(), LEFT_TEXTURE, DIR_LEFT_SYMBOL},
                     {Texture::RIGHT, QPixmap(), RIGHT_TEXTURE, DIR_RIGHT_SYMBOL},
                     {Texture::UP_RES, QPixmap(), UP_RES_TEXTURE, RESULT_UP_SYMBOL},
                     {Texture::DOWN_RES, QPixmap(), DOWN_RES_TEXTURE, RESULT_DOWN_SYMBOL},
                     {Texture::LEFT_RES, QPixmap(), LEFT_RES_TEXTURE, RESULT_LEFT_SYMBOL},
                     {Texture::RIGHT_RES, QPixmap(), RIGHT_RES_TEXTURE, RESULT_RIGHT_SYMBOL},
                     {Texture::UP_PROC, QPixmap(), UP_PROC_TEXTURE, PROCESSING_UP_SYMBOL},
                     {Texture::DOWN_PROC, QPixmap(), DOWN_PROC_TEXTURE, PROCESSING_DOWN_SYMBOL},
                     {Texture::LEFT_PROC, QPixmap(), LEFT_PROC_TEXTURE, PROCESSING_LEFT_SYMBOL},
                     {Texture::RIGHT_PROC, QPixmap(), RIGHT_PROC_TEXTURE, PROCESSING_RIGHT_SYMBOL} };

   mNumberTextures = { {QPixmap(), NUMBER_0_TEXTURE, 0},
                       {QPixmap(), NUMBER_1_TEXTURE, 1},
                       {QPixmap(), NUMBER_2_TEXTURE, 2},
                       {QPixmap(), NUMBER_3_TEXTURE, 3},
                       {QPixmap(), NUMBER_4_TEXTURE, 4},
                       {QPixmap(), NUMBER_5_TEXTURE, 5},
                       {QPixmap(), NUMBER_6_TEXTURE, 6},
                       {QPixmap(), NUMBER_7_TEXTURE, 7},
                       {QPixmap(), NUMBER_8_TEXTURE, 8},
                       {QPixmap(), NUMBER_9_TEXTURE, 9} };

   auto textureLoading = [](QPixmap& pixmap, const QString& texturePath, const int xCellSize, const int yCellSize)
   {
      if(pixmap.load(texturePath))
      {
         pixmap = pixmap.scaled(QSize(xCellSize, yCellSize), Qt::KeepAspectRatio);
      }
      else
      {
         qDebug() << "CMazeVisualizer::CMazeVisualizer() Error reading file " << texturePath;
      }
   };

   for (auto& texture : mCellTextures)
   {
      textureLoading(std::get<1>(texture), std::get<2>(texture), CELLSIZE, CELLSIZE);
   }

   for (auto& texture : mNumberTextures)
   {
      textureLoading(std::get<QPixmap>(texture), std::get<QString>(texture), NUMBERSIZEX, NUMBERSIZEY);
   }
}

void CMazeVisualizer::prepareWidgets(const int width, const int height)
{
   mCellLabelArray.reserve(width*height);
   mNumberLabelArray.reserve(width*height*2);
   const int intent = 4;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         std::unique_ptr<MazeLabel> cellLabel = std::make_unique<MazeLabel>();
         std::unique_ptr<MazeLabel> firstNumberLabel = std::make_unique<MazeLabel>();
         std::unique_ptr<MazeLabel> secondNumberLabel = std::make_unique<MazeLabel>();

         cellLabel->setGeometry(QRect(QPoint(x*CELLSIZE + x*MARGIN, y*CELLSIZE + y*MARGIN), QSize(CELLSIZE,CELLSIZE)));
         cellLabel->setPixmap(std::get<1>(mCellTextures[static_cast<int>(Texture::DEFAULT)]));
         firstNumberLabel->setGeometry(QRect(QPoint(x*CELLSIZE + x*MARGIN + intent, y*CELLSIZE + y*MARGIN), QSize(NUMBERSIZEX, NUMBERSIZEY)));
         firstNumberLabel->setPixmap(std::get<0>(mNumberTextures[0]));
         secondNumberLabel->setGeometry(QRect(QPoint(x*CELLSIZE + x*MARGIN + NUMBERSIZEX + intent, y*CELLSIZE + y*MARGIN), QSize(NUMBERSIZEX, NUMBERSIZEY)));
         secondNumberLabel->setPixmap(std::get<0>(mNumberTextures[0]));

         mCellLabelArray.push_back(std::move(cellLabel));
         mNumberLabelArray.push_back(std::move(firstNumberLabel));
         mNumberLabelArray.push_back(std::move(secondNumberLabel));
      }
   }

   for (const auto& label : mCellLabelArray)
   {
      connect(label.get(), &MazeLabel::clicked, this, &CMazeVisualizer::triggerClick);
   }
}

void CMazeVisualizer::draw(QWidget* widget) const
{
   draw(widget, mMazeCtrl.getMazeModel().getMazeData());
}

void CMazeVisualizer::draw(QWidget* widget, const std::vector<Cell>& mazeData) const
{
   const uint16_t width = mMazeCtrl.getMazeModel().getWidth();
   const uint16_t height = mMazeCtrl.getMazeModel().getHeight();

   for (auto& label : mCellLabelArray)
   {
      label->setParent(widget);
   }

   for (auto& label : mNumberLabelArray)
   {
      label->setParent(widget);
   }

   auto getIndex = [&](const Vector2D& point) -> uint16_t
   {
      return static_cast<uint16_t>(point.x + point.y * width);
   };

   for (uint8_t y = 0; y < height; y++)
   {
      for (uint8_t x = 0; x < width; x++)
      {
         const auto iter = std::find_if (mCellTextures.begin(), mCellTextures.end(), [&](const std::tuple<Texture, QPixmap, QString, char>& tuple)
         {
            if (getIndex(Vector2D(x,y)) < mazeData.size())
            {
               return std::get<char>(tuple) == mazeData[getIndex(Vector2D(x,y))].content;
            }
            else
            {
               return false;
            }
         } );

         mCellLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(*iter));
      }
   }

   widget->show();
}

uint16_t CMazeVisualizer::getCellSize() const
{
   return CELLSIZE;
}

uint16_t CMazeVisualizer::getCellMargin() const
{
   return MARGIN;
}

void CMazeVisualizer::triggerClick(const int x, const int y)
{
   mMazeCtrl.processMazeCellClick(x, y);
}
