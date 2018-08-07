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
   Cell* startCell = mMaze->getCell(ctr.getStartPoint());
   startCell->weight = 0;
   startCell->heuristicCost = calculateDistance(ctr.getStartPoint(), ctr.getEndPoint());
   startCell->totalCost = startCell->weight + startCell->heuristicCost;
   std::cout << "startCost = " << startCell->totalCost << std::endl;

   std::vector<Cell> closed;
   std::vector<Cell> open = { *startCell };
   std::vector<Cell> path;

   int i = 5;
   //while (open.size() > 0)
   while (i > 0)
   {
      i--;
      Cell* current = sortAndGetNearestNode(&open);

      if (current->content == GOAL_SYMBOL)
      {
         //construct path
      }
      else
      {
         //closed.push_back(open.at(0));
         current->processed = true;
         open.erase(open.begin());

         for (auto i : findNeighbours(*current))
         {
            float currentCost = i->weight + calculateDistance(i->coordinate, ctr.getEndPoint());
            std::cout << "elemPos=" << i->coordinate << " currentCost=" << currentCost << " totalCost=" << i->totalCost << std::endl;
            

            if (checkVectorOccurence(open, current))
            {
               open.push_back(*i);
            }
            else if (currentCost < i->totalCost)
            {
               i->cameFrom = current;
               i->totalCost = currentCost;
            }
            std::cout << open.size() << std::endl;
         }
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

std::vector<Cell*> CAStarMazeSolver::findNeighbours(const Cell& cell)
{
   Vector2D coors = cell.coordinate;
   Cell* upper = mMaze->getCell(Vector2D(coors.x, coors.y - 1));
   Cell* lower = mMaze->getCell(Vector2D(coors.x, coors.y + 1));
   Cell* left = mMaze->getCell(Vector2D(coors.x - 1, coors.y));
   Cell* right = mMaze->getCell(Vector2D(coors.x + 1, coors.y));

   auto checkAvailability = [](Cell* cell) -> bool
                            {
                              return cell != nullptr && cell->processed == false;
                            };

   std::vector<Cell*> v;
   for (auto node : { upper, lower, left, right })
   {
      if (checkAvailability(node)) v.push_back(node);
   }

   return v;
}

bool CAStarMazeSolver::checkVectorOccurence(const std::vector<Cell>& vec, Cell* node)
{
   for (auto i : vec)
   {
      if (i == *node) return true;
   }
}