#include <iostream>
#include <QLabel>
#include <QDebug>
#include "CMazeVisualizer.h"
#include "CMazeController.h"

#define CELLSIZE 40
#define MARGIN 5
const QString FILEPATH = ":/image/button.png";

CMazeVisualizer::CMazeVisualizer()
    :mDefaultTexture()
{
    if(mDefaultTexture.load(FILEPATH))
    {
        mDefaultTexture = mDefaultTexture.scaled(QSize(CELLSIZE, CELLSIZE), Qt::KeepAspectRatio);
    }
    else
    {
        qDebug() << "CMazeVisualizer::CMazeVisualizer() Error reading file";
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

    /*for (int y = 0; y < height; y++)
    {
       for (int x = 0; x < width; x++)
       {*/
          QLabel* pixmap = new QLabel;
          pixmap->setGeometry(QRect(QPoint(0, 0), QSize(40,40)));
          pixmap->setPixmap(mDefaultTexture);
          mLabelArray.push_back(pixmap);
       /*}
    }*/
}

void CMazeVisualizer::draw(QWidget* widget)
{
    for (auto i : mLabelArray)
    {
        i->setParent(widget);
    }

    widget->show();

   /*CMazeModel* model = CMazeController::getMazeController().getMazeModel().get();

   for (int y = 0; y < model->getHeight(); y++)
   {
      for (int x = 0; x < model->getWidth(); x++)
      {
         std::cout << model->getCellContent(Vector2D(x,y));
      }
      std::cout << std::endl;
   }*/
}
