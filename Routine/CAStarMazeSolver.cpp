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

   if (!ctr.getMazeModel()->isEndPointSet() || !ctr.getMazeModel()->isStartPointSet())
   {
      std::cout << "START or END point is not set " << std::endl;
      return;
   }
   
   Cell* startCell = mMaze->getCell(ctr.getStartPoint());
   //startCell->weight = 0;
   startCell->heuristicCost = calculateDistance(ctr.getStartPoint(), ctr.getEndPoint());
   startCell->totalCost = startCell->weight + startCell->heuristicCost;
   std::cout << "startCost = " << startCell->totalCost << std::endl;

   std::vector<Cell> closed;
   std::vector<Cell*> open = { startCell };
   std::vector<Cell> path;

   int i = 5;
   while (open.size() > 0)
   //while (i > 0)
   {
      i--;
      Cell* current = sortAndGetNearestNode(&open);

      if (current->content == GOAL_SYMBOL)
      {
         //construct path
         std::cout << "GOAL FOUND" << current->coordinate << std::endl;
         return;
      }
      else
      {
         //closed.push_back(open.at(0));
         current->processed = true;
         open.erase(open.begin());

         std::cout << "*******************************" << std::endl;
         std::cout << "ANALYZING " << current->coordinate << " processed=" << current->processed << std::endl;
         std::cout << "*******************************" << std::endl;

         for (auto i : findNeighbours(*current))
         {
            float currentCost = i->weight + calculateDistance(i->coordinate, ctr.getEndPoint());
            std::cout << "BEFORE elemPos=" << i->coordinate << " currentCost=" << currentCost << " totalCost=" << i->totalCost << std::endl;
            

            if (!checkVectorOccurence(open, *i))
            {
               std::cout << "WRITE TO VECTOR" << std::endl;
               open.push_back(i);
            }
            else if (currentCost < i->totalCost)
            {
               std::cout << "PROCESS" << std::endl;
               i->cameFrom = current;
               i->totalCost = currentCost;
            }

            std::cout << "AFTER elemPos=" << i->coordinate << " currentCost=" << currentCost << " totalCost=" << i->totalCost << std::endl;
            std::cout << open.size() << std::endl;
            std::cout << "=====================================" << std::endl;
         }
      }
   }

   
}

float CAStarMazeSolver::calculateDistance(const Vector2D& start, const Vector2D& end)
{
   return sqrt(pow(end.x - start.x,2) + pow(end.y - start.y, 2));
}

Cell* CAStarMazeSolver::sortAndGetNearestNode(std::vector<Cell*>* array)
{
   std::sort(array->begin(), array->end(), [](Cell* s1, Cell* s2) -> bool
                                         { return s1->totalCost < s2->totalCost; } );
   return array->at(0);
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
      if (node)
      {
         std::cout << "findNeighbours " << node->coordinate << " processed=" << node->processed << std::endl;
         if (checkAvailability(node)) v.push_back(node);
      }
   }

   return v;
}

bool CAStarMazeSolver::checkVectorOccurence(const std::vector<Cell*>& vec, const Cell& node)
{
   bool result = false;

   if (vec.size() == 0)
   {
      std::cout << "SIZE==0" << std::endl;
      result = true;
   }
   else
   {
      std::cout << "vec.size()=" << vec.size() << std::endl;
      for (auto i : vec)
      {
         std::cout << "======>i.coor=" << i->coordinate << " node.coor=" << node.coordinate << std::endl;
         if (*i == node) return true;
      }
   }
   
   return false;
}