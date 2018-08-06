#include "CAStarMazeSolver.h"
#include <iostream>
#include <algorithm>

bool wayToSort(Cell i, Cell j) { return i.totalCost > j.totalCost; }

CAStarMazeSolver::CAStarMazeSolver(std::shared_ptr<CMazeModel> maze)
   :mMaze(maze)
{
}

void CAStarMazeSolver::solve()
{
   CMazeController& ctr = CMazeController::getMazeController();
   std::vector<Cell> closed;
   std::vector<Cell> open = { *(ctr.getMazeModel()->getCell(ctr.getStartPoint())) };
   std::vector<Cell> path;

   Cell* startCell = ctr.getMazeModel()->getCell(ctr.getStartPoint());
   startCell->weight = 0;
   startCell->heuristicCost = calculateDistance(ctr.getStartPoint(), ctr.getEndPoint());
   startCell->totalCost = startCell->weight + startCell->heuristicCost;

   std::cout << "startCost = " << startCell->totalCost << std::endl;

   while (open.size() > 0)
   {
      Cell* current = sortAndGetNearestNode(&open);

      if (current->content == GOAL_SYMBOL)
      {
         //construct path
      }
      else
      {
         closed.push_back(open.at(0));
         open.erase(open.begin());


      }
   }
}

float CAStarMazeSolver::calculateDistance(const Vector2D& start, const Vector2D& end)
{
   return sqrt(pow(end.x - start.x,2) + pow(end.y - start.y, 2));
}

Cell* CAStarMazeSolver::sortAndGetNearestNode(std::vector<Cell>* array)
{
   std::sort(array->begin(), array->end(), [](const Cell& s1, const Cell& s2) -> bool
                                         { return s1.totalCost < s2.totalCost; } );

   return &array->at(0);
}