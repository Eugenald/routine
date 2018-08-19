#pragma once

#include <vector>

struct Cell;

class CMazeSolutionStorage
{
public:
   explicit CMazeSolutionStorage(uint16_t expectedAmount = 0);

   const std::vector<Cell>* getModelDataAt(const uint32_t index) const;
   uint32_t getStorageSize() const;
   void pushBackModelData(const std::vector<Cell>& modelData);
   void clearStorage();

private:
   std::vector<std::vector<Cell>> mModelStorage;
};
