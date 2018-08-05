#pragma once

class Maze;

class CVisualizer
{
public:
   CVisualizer(const CVisualizer&) = delete;
   CVisualizer& operator= (const CVisualizer&) = delete;

   static CVisualizer& getVizualizer();
   void draw(const Maze& maze);

private:
   CVisualizer() = default;
   ~CVisualizer() = default;
};