#pragma once

#include <vector>
#include "Vector2D.h"

struct Maze
{
   Maze(const int _width, const int _height)
      : width(_width)
      , height(_height)
   {
      content.reserve(width*height);
      for (int i = 0; i < width*height; i++)
      {
         content.push_back('-');
      }
   }

   int width;
   int height;
   std::vector<char> content;
};

class CMazeCreator
{
public:
   CMazeCreator(const CMazeCreator&) = delete;
   CMazeCreator& operator= (const CMazeCreator&) = delete;

   static CMazeCreator& getMazeCreator(const int width, const int height);

   Maze& getMaze();
   void setStartPoint(const Vector2D& point);
   void setEndPoint(const Vector2D& point);
   Vector2D& getStartPoint();
   Vector2D& getEndPoint();

private:
   CMazeCreator(const int width, const int height);
   CMazeCreator() = default;
   ~CMazeCreator() = default;

   void fillMaze();

private:
   Maze mMaze;
   Vector2D mStartPoint;
   Vector2D mEndPoint;
};