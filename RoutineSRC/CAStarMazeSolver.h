#pragma once

#include <memory>
#include <vector>
#include <functional>

struct Cell;
class CMazeModel;
class Vector2D;

enum class ArrowType: char{ COMMON, RESULT, PROCESSING};

class CAStarMazeSolver
{
public:
   explicit CAStarMazeSolver(CMazeModel& mazeCtrl);
   ~CAStarMazeSolver() = default;

   void solve();
   void setAlgorithmIterationCallback(std::function<void()>& callback);
   std::function<void()>& getRecalculationCallback();

private:
   float calculateDistance(const Vector2D& start, const Vector2D& end);
   std::vector<Cell*> findNeighbours(const Cell& cell) const;

   static Cell* sortAndGetNearestNode(std::vector<Cell*>& array);
   static bool checkVectorOccurence(const std::vector<Cell*>& vec, const Cell& node);
   static void restorePathToGoal(Cell* goal);
   static char getDirTo(const Vector2D& child, const Vector2D& parent, const ArrowType resultDir = ArrowType::COMMON);
   static char restoreCommonState(char prevState);

private:
   CMazeModel& mMaze;
   std::function<void()> mIterationCallback;
};
