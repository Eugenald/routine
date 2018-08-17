#include "CMazeSolutionStorage.h"
#include "CMazeModel.h"

CMazeSolutionStorage::CMazeSolutionStorage(uint16_t expectedAmount /*=0*/)
{
    if (expectedAmount != 0)
    {
        mModelStorage.reserve(expectedAmount);
    }
}

const CMazeModel* CMazeSolutionStorage::getModelAt(const uint16_t index) const
{
    return index < mModelStorage.size() ? &mModelStorage[index] : nullptr;
}

int CMazeSolutionStorage::getStorageSize() const
{
    return mModelStorage.size();
}

void CMazeSolutionStorage::pushBackModel(const CMazeModel& model)
{
    mModelStorage.push_back(model);
}

void CMazeSolutionStorage::clearStorage()
{
    mModelStorage.clear();
}
