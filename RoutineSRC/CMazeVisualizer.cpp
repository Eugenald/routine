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

CMazeVisualizer::CMazeVisualizer()
    : mDefaultTexture()
    , mTextures()
    , mLabelArray()
{
    mTextures = { {Texture::DEFAULT, QPixmap(), DEFAULT_TEXTURE},
                  {Texture::GOAL, QPixmap(), GOAL_TEXTURE},
                  {Texture::START, QPixmap(), START_TEXTURE},
                  {Texture::UP, QPixmap(), UP_TEXTURE},
                  {Texture::DOWN, QPixmap(), DOWN_TEXTURE},
                  {Texture::LEFT, QPixmap(), LEFT_TEXTURE},
                  {Texture::RIGHT, QPixmap(), RIGHT_TEXTURE},
                  {Texture::UP_RES, QPixmap(), UP_RES_TEXTURE},
                  {Texture::DOWN_RES, QPixmap(), DOWN_RES_TEXTURE},
                  {Texture::LEFT_RES, QPixmap(), LEFT_RES_TEXTURE},
                  {Texture::RIGHT_RES, QPixmap(), RIGHT_RES_TEXTURE}, };

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

CMazeVisualizer& CMazeVisualizer::getVizualizer()
{
   static CMazeVisualizer instance;
   return instance;
}

void CMazeVisualizer::prepareWidgets(const int width, const int height)
{
    mLabelArray.reserve(width*height);

    for (int y = 0; y < height; y++)
    {
       for (int x = 0; x < width; x++)
       {
          QLabel* pixmap = new QLabel;
          pixmap->setGeometry(QRect(QPoint(x*CELLSIZE + x*MARGIN, y*CELLSIZE + y*MARGIN), QSize(CELLSIZE,CELLSIZE)));

          pixmap->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::DEFAULT)]));
          mLabelArray.push_back(pixmap);
       }
    }
}

void CMazeVisualizer::draw(QWidget* widget)
{

    CMazeModel* model = CMazeController::getMazeController().getMazeModel().get();

    for (auto i : mLabelArray)
    {
        i->setParent(widget);
    }

    auto getIndex = [&](const Vector2D& point)
                    {
                       return point.x + point.y * model->getWidth();
                    };

   for (uint8_t y = 0; y < model->getHeight(); y++)
   {
      for (uint8_t x = 0; x < model->getWidth(); x++)
      {
          switch(model->getCellContent(Vector2D(x,y)))
          {
              case GOAL_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::GOAL)]));
                  break;
              case START_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::START)]));
                  break;
              case PATH_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::DEFAULT)]));
                  break;
              case DIR_UP_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::UP)]));
                  break;
              case DIR_DOWN_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::DOWN)]));
                  break;
              case DIR_LEFT_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::LEFT)]));
                  break;
              case DIR_RIGHT_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::RIGHT)]));
                  break;
              case DIR_UP_RES_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::UP_RES)]));
                  break;
              case DIR_DOWN_RES_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::DOWN_RES)]));
                  break;
              case DIR_LEFT_RES_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::LEFT_RES)]));
                  break;
              case DIR_RIGHT_RES_SYMBOL:
                  mLabelArray[getIndex(Vector2D(x,y))]->setPixmap(std::get<1>(mTextures[static_cast<int>(Texture::RIGHT_RES)]));
                  break;
              default:
                  break;
          }
      }
   }

   widget->show();
}
