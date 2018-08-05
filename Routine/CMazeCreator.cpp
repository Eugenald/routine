#include "CMazeCreator.h"
#include <iostream>

CMazeCreator::CMazeCreator(const int width, const int height)
   : mMaze(width, height)
{
   fillMaze();
}

CMazeCreator& CMazeCreator::getMazeCreator(const int width, const int height)
{
   static CMazeCreator instance(width, height);
   return instance;
}

Maze& CMazeCreator::getMaze()
{
   return mMaze;
}

void CMazeCreator::setStartPoint(const Vector2D& point)
{
   mStartPoint = point;

   int index = point.x + point.y * mMaze.width;

   std::cout << "CMazeCreator::setStartPoint X = " << point.x << " Y = " << point.y << std::endl;
   std::cout << "CMazeCreator::setStartPoint index = " << index << std::endl;

   if (index < mMaze.content.size())
   {
      mMaze.content[index] = '*';
   }
}

void CMazeCreator::setEndPoint(const Vector2D& point)
{
   mEndPoint = point;

   int index = point.x + point.y * mMaze.height;

   std::cout << "CMazeCreator::setEndPoint X = " << point.x << " Y = " << point.y << std::endl;
   std::cout << "CMazeCreator::setEndPoint index = " << index << std::endl;

   if (index < mMaze.content.size())
   {
      mMaze.content[index] = '1';
   }
}

Vector2D& CMazeCreator::getStartPoint()
{
   return mStartPoint;
}

Vector2D& CMazeCreator::getEndPoint() 
{
   return mEndPoint;
}

void CMazeCreator::fillMaze()
{
   for (int i = 0; i < mMaze.height; i++)
   {
      for (int j = 0; j < mMaze.width; j++)
      {
         mMaze.content[i*mMaze.width + j] = '0';
      }
   }
}