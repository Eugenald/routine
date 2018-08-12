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
   startCell->heuristicCost = calculateDistance(ctr.getStartPoint(), ctr.getEndPoint());
   startCell->totalCost = startCell->weight + startCell->heuristicCost;
   std::cout << "startCost = " << startCell->totalCost << std::endl;

   std::vector<Cell*> open = { startCell };

   //int i = 5;
   while (open.size() > 0)
   //while (i > 0)
   {
      //i--;
      Cell* current = sortAndGetNearestNode(&open);

      /*if (current->content == GOAL_SYMBOL)
      {
         std::cout << "GOAL FOUND " << current->coordinate << std::endl;
         restorePathToGoal(current);
         return;
      }
      else
      {*/
         current->processed = true;
         open.erase(open.begin());

         std::cout << "*******************************" << std::endl;
         std::cout << "ANALYZING " << current->coordinate << " processed=" << current->processed << std::endl;
         std::cout << "*******************************" << std::endl;

         for (auto i : findNeighbours(*current))
         {
            float currentCost = i->weight + calculateDistance(i->coordinate, ctr.getEndPoint());
            std::cout << "BEFORE elemPos=" << i->coordinate << " currentCost=" << currentCost << " totalCost=" << i->totalCost << std::endl;
            i->cameFrom = current;

            if (!checkVectorOccurence(open, *i))
            {
               std::cout << "WRITE TO VECTOR" << std::endl;
               open.push_back(i);
            }
            else if (currentCost < i->totalCost)
            {
               std::cout << "PROCESS" << std::endl;
               i->totalCost = currentCost;

               if (i->content != GOAL_SYMBOL)
               {
                   i->content = getDirTo(i->coordinate, current->coordinate);
               }
               else
               {
                   std::cout << "GOAL FOUND " << current->coordinate << std::endl;
                   restorePathToGoal(current);
                   return;
               }
            }

            std::cout << "AFTER elemPos=" << i->coordinate << " currentCost=" << currentCost << " totalCost=" << i->totalCost << std::endl;
            std::cout << open.size() << std::endl;
            std::cout << "=====================================" << std::endl;
         }
      //}
   }

   
}

float CAStarMazeSolver::calculateDistance(const Vector2D& start, const Vector2D& end)
{
   return static_cast<float>(sqrt(pow(end.x - start.x,2) + pow(end.y - start.y, 2)));
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
         //std::cout << "findNeighbours " << node->coordinate << " processed=" << node->processed << std::endl;
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
      //std::cout << "vec.size()=" << vec.size() << std::endl;
      for (auto i : vec)
      {
         //std::cout << "======>i.coor=" << i->coordinate << " node.coor=" << node.coordinate << std::endl;
         if (*i == node) return true;
      }
   }
   
   return false;
}

void CAStarMazeSolver::restorePathToGoal(Cell* goal)
{
   Cell* currentNode = goal->cameFrom;

   while (currentNode)
   {
       if (currentNode->cameFrom != nullptr)
       {
           std::cout << "currentNode" << currentNode->coordinate << std::endl;
           currentNode->content = getDirTo(currentNode->coordinate, currentNode->cameFrom->coordinate, true);

       }
       currentNode = currentNode->cameFrom;
   }
}

char CAStarMazeSolver::getDirTo(const Vector2D& from, const Vector2D& to, const bool resultDir)
{
    Vector2D diff = from;
    diff -= to;
    char result = PATH_SYMBOL;

    if (diff.x == 1 && diff.y == 0)
    {
        result = resultDir ? DIR_UP_RES_SYMBOL : DIR_UP_SYMBOL;
    }
    else if (diff.x == -1 && diff.y == 0)
    {
        result = resultDir ? DIR_DOWN_RES_SYMBOL : DIR_DOWN_SYMBOL;
    }
    else if (diff.x == 0 && diff.y == 1)
    {
        result = resultDir ? DIR_LEFT_RES_SYMBOL : DIR_LEFT_SYMBOL;
    }
    else if (diff.x == 0 && diff.y == -1)
    {
        result = resultDir ? DIR_RIGHT_RES_SYMBOL : DIR_RIGHT_SYMBOL;
    }

    return result;
}
