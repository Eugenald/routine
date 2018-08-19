#include "CAStarMazeSolver.h"
#include "mazeModel\CMazeModel.h"
#include <iostream>
#include <algorithm>

CAStarMazeSolver::CAStarMazeSolver(CMazeModel& maze)
   : mMaze(maze)
{
}

void CAStarMazeSolver::solve()
{   
   Cell* startCell = mMaze.getCell(mMaze.getStartPoint());
   startCell->heuristicCost = calculateDistance(mMaze.getStartPoint(), mMaze.getEndPoint());
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
         mIterationCallback();
         return;
      }

      current->content = restoreCommonState(current->content);
      current->processed = true;
      cellsForAnalysis.pop_back();

      std::cout << "*******************************" << std::endl;
      std::cout << "ANALYZING " << current->coordinate << " processed=" << current->processed << std::endl;
      std::cout << "*******************************" << std::endl;

      for (auto neighbourCell : findNeighbours(*current))
      {
         float currentCost = neighbourCell->weight + calculateDistance(neighbourCell->coordinate, mMaze.getEndPoint());
         neighbourCell->cameFrom = current;

         if (currentCost < neighbourCell->totalCost)
         {
            std::cout << "PROCESS" << std::endl;
            neighbourCell->totalCost = currentCost;

            if (neighbourCell->content != GOAL_SYMBOL)
            {
               neighbourCell->content = getDirTo(current->coordinate, neighbourCell->coordinate);
            }
         }

         if (!checkVectorOccurence(cellsForAnalysis, *neighbourCell))
         {
            std::cout << "WRITE TO VECTOR" << std::endl;
            cellsForAnalysis.push_back(neighbourCell);
            if (neighbourCell->content != GOAL_SYMBOL)
            {
               neighbourCell->content = getDirTo(current->coordinate, neighbourCell->coordinate, ArrowType::PROCESSING);
            }
         }

         std::cout << "AFTER elemPos=" << neighbourCell->coordinate << " currentCost=" << currentCost << " totalCost=" << neighbourCell->totalCost << std::endl;
         std::cout << cellsForAnalysis.size() << std::endl;
         std::cout << "=====================================" << std::endl;
      }

      mIterationCallback();
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
   Cell* upper = mMaze.getCell(Vector2D(coors.x, coors.y - 1));
   Cell* lower = mMaze.getCell(Vector2D(coors.x, coors.y + 1));
   Cell* left = mMaze.getCell(Vector2D(coors.x - 1, coors.y));
   Cell* right = mMaze.getCell(Vector2D(coors.x + 1, coors.y));

   auto checkAvailability = [](Cell* cell) -> bool
   {
      return cell != nullptr && cell->processed == false && cell->content != OBSTACLE_SYMBOL;
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

void CAStarMazeSolver::setAlgorithmIterationCallback(std::function<void()>& callback)
{
   mIterationCallback = callback;
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
         currentNode->content = getDirTo(currentNode->cameFrom->coordinate, currentNode->coordinate, ArrowType::RESULT);
      }
      currentNode = currentNode->cameFrom;
   }
}

char CAStarMazeSolver::getDirTo(const Vector2D& from, const Vector2D& to,  const ArrowType resultDir/* = ArrowType::COMMON*/)
{
#define GETARROWCHAR(DIRECTION) \
   switch(resultDir) \
   { \
      case ArrowType::COMMON: \
         result = DIR_##DIRECTION##_SYMBOL; \
         break; \
      case ArrowType::RESULT: \
         result = RESULT_##DIRECTION##_SYMBOL; \
         break; \
      case ArrowType::PROCESSING: \
         result = PROCESSING_##DIRECTION##_SYMBOL; \
         break; \
   }

   Vector2D diff = from;
   diff -= to;
   char result = DEFAULT_SYMBOL;

   if (diff.x == 1 && diff.y == 0)
   {
      GETARROWCHAR(LEFT);
   }
   else if (diff.x == -1 && diff.y == 0)
   {
      GETARROWCHAR(RIGHT);
   }
   else if (diff.x == 0 && diff.y == 1)
   {
      GETARROWCHAR(UP);
   }
   else if (diff.x == 0 && diff.y == -1)
   {
      GETARROWCHAR(DOWN);
   }

   return result;
}

char CAStarMazeSolver::restoreCommonState(char prevState)
{
   switch(prevState)
   {
      case PROCESSING_LEFT_SYMBOL: return DIR_LEFT_SYMBOL;
      case PROCESSING_RIGHT_SYMBOL: return DIR_RIGHT_SYMBOL;
      case PROCESSING_UP_SYMBOL: return DIR_UP_SYMBOL;
      case PROCESSING_DOWN_SYMBOL: return DIR_DOWN_SYMBOL;
      default: return prevState;
   }
}
