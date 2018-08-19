#include "CMazeSolutionStorage.h"
#include "CMazeModel.h"

CMazeSolutionStorage::CMazeSolutionStorage(uint16_t expectedAmount /*=0*/)
{
   if (expectedAmount != 0)
   {
      mModelStorage.reserve(expectedAmount);
   }
}

const std::vector<Cell>* CMazeSolutionStorage::getModelDataAt(const uint32_t index) const
{
   return index < mModelStorage.size() ? &mModelStorage[index] : nullptr;
}

uint32_t CMazeSolutionStorage::getStorageSize() const
{
   return mModelStorage.size();
}

void CMazeSolutionStorage::pushBackModelData(const std::vector<Cell>& modelData)
{
   mModelStorage.push_back(modelData);
}

void CMazeSolutionStorage::clearStorage()
{
   mModelStorage.clear();
}
