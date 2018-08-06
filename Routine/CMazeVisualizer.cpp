#include <iostream>
#include "CMazeVisualizer.h"
#include "CMazeController.h"

CMazeVisualizer& CMazeVisualizer::getVizualizer()
{
   static CMazeVisualizer instance;
   return instance;
}

void CMazeVisualizer::draw()
{
   CMazeModel* model = CMazeController::getMazeController().getMazeModel().get();

   for (int y = 0; y < model->getHeight(); y++)
   {
      for (int x = 0; x < model->getWidth(); x++)
      {
         std::cout << model->getCellContent(Vector2D(x,y));
      }
      std::cout << std::endl;
   }

   for (int i = 0; i < model->getWidth(); i++)
   {
      std::cout << "=";
   }
   std::cout << std::endl;
}