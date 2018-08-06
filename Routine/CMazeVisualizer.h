#pragma once

class CMazeVisualizer
{
public:
   CMazeVisualizer(const CMazeVisualizer&) = delete;
   CMazeVisualizer& operator= (const CMazeVisualizer&) = delete;

   static CMazeVisualizer& getVizualizer();
   void draw();

private:
   CMazeVisualizer() = default;
   ~CMazeVisualizer() = default;
};