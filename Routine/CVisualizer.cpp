#include <iostream>
#include "CVisualizer.h"
#include "CMazeCreator.h"

CVisualizer& CVisualizer::getVizualizer()
{
   static CVisualizer instance;
   return instance;
}

void CVisualizer::draw(const Maze& maze)
{
   int lineBreaker = 0;
   for (int i = 0; i < maze.content.size(); i++)
   {
      std::cout << maze.content[i];

      lineBreaker++;
      if (maze.width == lineBreaker)
      {
         lineBreaker = 0;
         std::cout << std::endl;
      }
   }

   for (int i = 0; i < maze.width; i++)
   {
      std::cout << "=";
   }
   std::cout << std::endl;
}