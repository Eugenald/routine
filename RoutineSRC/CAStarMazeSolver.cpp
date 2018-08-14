#include "CAStarMazeSolver.h"
#include <iostream>
#include <algorithm>

CAStarMazeSolver::CAStarMazeSolver(CMazeController& mazeCtrl)
   : mMazeCtrl(mazeCtrl)
{
}

void CAStarMazeSolver::solve()
{
   if (!mMazeCtrl.getMazeModel()->isEndPointSet() || !mMazeCtrl.getMazeModel()->isStartPointSet())
   {
      std::cout << "START or END point is not set " << std::endl;
      return;
   }
   
   Cell* startCell = mMazeCtrl.getMazeModel()->getCell(mMazeCtrl.getStartPoint());
   startCell->heuristicCost = calculateDistance(mMazeCtrl.getStartPoint(), mMazeCtrl.getEndPoint());
   startCell->totalCost = startCell->weight + startCell->heuristicCost;
   std::cout << "startCost = " << startCell->totalCost << std::endl;

   std::vector<Cell*> cellsForAnalysis = { startCell };

   while (!cellsForAnalysis.empty())
   {
      Cell* current = sortAndGetNearestNode(cellsForAnalysis);

      if (current->content == GOAL_SYMBOL)
      {
         std::cout << "GOAL FOUND " << current->coordinate << std::endl;
         restorePathToGoal(current);
         return;
      }

      current->processed = true;
      cellsForAnalysis.pop_back();

      std::cout << "*******************************" << std::endl;
      std::cout << "ANALYZING " << current->coordinate << " processed=" << current->processed << std::endl;
      std::cout << "*******************************" << std::endl;

      for (auto neighbourCell : findNeighbours(*current))
      {
         float currentCost = neighbourCell->weight + calculateDistance(neighbourCell->coordinate, mMazeCtrl.getEndPoint());
         neighbourCell->cameFrom = current;

         if (!checkVectorOccurence(cellsForAnalysis, *neighbourCell))
         {
            std::cout << "WRITE TO VECTOR" << std::endl;
            cellsForAnalysis.push_back(neighbourCell);
         }

         if (currentCost < neighbourCell->totalCost)
         {
            std::cout << "PROCESS" << std::endl;
            neighbourCell->totalCost = currentCost;

            if (neighbourCell->content != GOAL_SYMBOL)
            {
                neighbourCell->content = getDirTo(current->coordinate, neighbourCell->coordinate);
            }
         }

         std::cout << "AFTER elemPos=" << neighbourCell->coordinate << " currentCost=" << currentCost << " totalCost=" << neighbourCell->totalCost << std::endl;
         std::cout << cellsForAnalysis.size() << std::endl;
         std::cout << "=====================================" << std::endl;
      }
   }
}

float CAStarMazeSolver::calculateDistance(const Vector2D& start, const Vector2D& end)
{
   return static_cast<float>(sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)));
}

Cell* CAStarMazeSolver::sortAndGetNearestNode(std::vector<Cell*>& array)
{
   std::sort(array.begin(), array.end(), [](Cell* s1, Cell* s2) -> bool
                                         { return s1->totalCost > s2->totalCost; } );
   /*std::cout << "sortAndGetNearestNode " << std::endl;
   for (auto i : *array)
   {
       std::cout << i->coordinate << " cost=" << i->totalCost << std::endl;
   }*/

   return array.back();
}

std::vector<Cell*> CAStarMazeSolver::findNeighbours(const Cell& cell) const
{
   Vector2D coors = cell.coordinate;
   Cell* upper = mMazeCtrl.getMazeModel()->getCell(Vector2D(coors.x, coors.y - 1));
   Cell* lower = mMazeCtrl.getMazeModel()->getCell(Vector2D(coors.x, coors.y + 1));
   Cell* left = mMazeCtrl.getMazeModel()->getCell(Vector2D(coors.x - 1, coors.y));
   Cell* right = mMazeCtrl.getMazeModel()->getCell(Vector2D(coors.x + 1, coors.y));

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
  //std::cout << "vec.size()=" << vec.size() << std::endl;
   std::find_if(vec.begin(), vec.end(), [&](Cell* cell) {return *cell == node;} );
   
   return false;
}

void CAStarMazeSolver::restorePathToGoal(Cell* goal)
{
   Cell* currentNode = goal->cameFrom;

   while (currentNode)
   {
       if (currentNode->cameFrom != nullptr)
       {
           std::cout << "currentNode=" << currentNode->coordinate << " cameFrom=" << currentNode->cameFrom->coordinate << std::endl;
           currentNode->content = getDirTo(currentNode->cameFrom->coordinate, currentNode->coordinate, true);

       }
       currentNode = currentNode->cameFrom;
   }
}

char CAStarMazeSolver::getDirTo(const Vector2D& from, const Vector2D& to, const bool resultDir /*=false*/)
{
    Vector2D diff = from;
    diff -= to;
    char result = PATH_SYMBOL;

    if (diff.x == 1 && diff.y == 0)
    {
        result = resultDir ? DIR_LEFT_RES_SYMBOL : DIR_LEFT_SYMBOL;
    }
    else if (diff.x == -1 && diff.y == 0)
    {
        result = resultDir ? DIR_RIGHT_RES_SYMBOL : DIR_RIGHT_SYMBOL;
    }
    else if (diff.x == 0 && diff.y == 1)
    {
        result = resultDir ? DIR_UP_RES_SYMBOL : DIR_UP_SYMBOL;
    }
    else if (diff.x == 0 && diff.y == -1)
    {
        result = resultDir ? DIR_DOWN_RES_SYMBOL : DIR_DOWN_SYMBOL;
    }

    return result;
}
