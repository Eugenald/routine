#include <iostream>
#include <QLabel>
#include <QDebug>
#include "CMazeVisualizer.h"
#include "CMazeController.h"

#define CELLSIZE 40
#define MARGIN 5
const QString DEFAULT_TEXTURE = ":/images/button.png";
const QString GOAL_TEXTURE = ":/images/goal.png";
const QString START_TEXTURE = ":/images/start.png";
const QString UP_TEXTURE = ":/images/up.png";
const QString DOWN_TEXTURE = ":/images/down.png";
const QString LEFT_TEXTURE = ":/images/left.png";
const QString RIGHT_TEXTURE = ":/images/right.png";
const QString UP_RES_TEXTURE = ":/images/resultUp.png";
const QString DOWN_RES_TEXTURE = ":/images/resultDown.png";
const QString LEFT_RES_TEXTURE = ":/images/resultLeft.png";
const QString RIGHT_RES_TEXTURE = ":/images/resultRight.png";
const QString OBSTACLE_TEXTURE = ":/images/obstacle.png";

CMazeVisualizer::CMazeVisualizer(CMazeController& mazeCtrl)
   : mMazeCtrl(mazeCtrl)
   , mDefaultTexture()
   , mTextures()
   , mLabelArray()
{
   mTextures = { {Texture::DEFAULT, QPixmap(), DEFAULT_TEXTURE, '0'},
                 {Texture::GOAL, QPixmap(), GOAL_TEXTURE, GOAL_SYMBOL},
                 {Texture::START, QPixmap(), START_TEXTURE, START_SYMBOL},
                 {Texture::UP, QPixmap(), UP_TEXTURE, DIR_UP_SYMBOL},
                 {Texture::DOWN, QPixmap(), DOWN_TEXTURE, DIR_DOWN_SYMBOL},
                 {Texture::LEFT, QPixmap(), LEFT_TEXTURE, DIR_LEFT_SYMBOL},
                 {Texture::RIGHT, QPixmap(), RIGHT_TEXTURE, DIR_RIGHT_SYMBOL},
                 {Texture::UP_RES, QPixmap(), UP_RES_TEXTURE, DIR_UP_RES_SYMBOL},
                 {Texture::DOWN_RES, QPixmap(), DOWN_RES_TEXTURE, DIR_DOWN_RES_SYMBOL},
                 {Texture::LEFT_RES, QPixmap(), LEFT_RES_TEXTURE, DIR_LEFT_RES_SYMBOL},
                 {Texture::RIGHT_RES, QPixmap(), RIGHT_RES_TEXTURE, DIR_RIGHT_RES_SYMBOL},
                 {Texture::RIGHT_RES, QPixmap(), OBSTACLE_TEXTURE, OBSTACLE_SYMBOL} };

   auto textureLoading = [](QPixmap& pixmap, const QString& texturePath)
   {
      if(pixmap.load(texturePath))
      {
         pixmap = pixmap.scaled(QSize(CELLSIZE, CELLSIZE), Qt::KeepAspectRatio);
      }
      else
      {
         qDebug() << "CMazeVisualizer::CMazeVisualizer() Error reading file " << texturePath;
      }
   };

   for (auto& i : mTextures)
   {
      textureLoading(std::get<1>(i), std::get<2>(i));
   }
}

CMazeVisualizer::~CMazeVisualizer()
{
   for (auto i : mLabelArray)
   {
      delete i;
   }
}

void CMazeVisualizer::prepareWidgets(const int width, const int height)
{
   mLabelArray.reserve(width*height);

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         MazeLabel* pixmap = new MazeLabel;

         pixmap->setGeometry(QRect(QPoint(x*CELLSIZE + x*MARGIN, y*CELLSIZE + y*MARGIN), QSize(CELLSIZE,CELLSIZE)));
         pixmap->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::DEFAULT)]));
         mLabelArray.push_back(pixmap);
      }
   }

   for (auto i : mLabelArray)
   {
      connect(i, &MazeLabel::clicked, this, &CMazeVisualizer::triggerClick);
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

   for (auto i : mLabelArray)
   {
      i->setParent(widget);
   }

   auto getIndex = [&](const Vector2D& point) -> uint16_t
   {
      return static_cast<uint16_t>(point.x + point.y * width);
   };

   for (uint8_t y = 0; y < height; y++)
   {
      for (uint8_t x = 0; x < width; x++)
      {
         auto iter = std::find_if (mTextures.begin(), mTextures.end(), [&](const std::tuple<Texture, QPixmap, QString, char>& tuple)
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

         mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(*iter));
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
