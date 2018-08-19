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
   return index < mModelStorage.size() ? &mModelStorage[index].first : nullptr;
}

QString CMazeSolutionStorage::getModelDebugInfoAt(const uint32_t index) const
{
   return index < mModelStorage.size() ? mModelStorage[index].second : QString();
}

uint32_t CMazeSolutionStorage::getStorageSize() const
{
   return mModelStorage.size();
}

void CMazeSolutionStorage::pushBackModelData(const std::vector<Cell>& modelData, const QString debugInfo /*= QString()*/ )
{
   mModelStorage.push_back(std::make_pair(modelData, debugInfo));
}

void CMazeSolutionStorage::clearStorage()
{
   mModelStorage.clear();
}
