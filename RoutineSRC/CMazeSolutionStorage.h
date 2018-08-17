#pragma once

#include <vector>

class CMazeModel;

class CMazeSolutionStorage
{
public:
   explicit CMazeSolutionStorage(uint16_t expectedAmount = 0);

   const CMazeModel* getModelAt(const uint32_t index) const;
   uint32_t getStorageSize() const;
   void pushBackModel(const CMazeModel& model);
   void clearStorage();

private:
   std::vector<CMazeModel> mModelStorage;
};
