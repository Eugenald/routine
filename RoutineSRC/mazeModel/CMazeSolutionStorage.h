#pragma once

#include <vector>
#include <QString>

struct Cell;

class CMazeSolutionStorage
{
public:
   explicit CMazeSolutionStorage(uint16_t expectedAmount = 0);

   const std::vector<Cell>* getModelDataAt(const uint32_t index) const;
   QString getModelDebugInfoAt(const uint32_t index) const;
   uint32_t getStorageSize() const;
   void pushBackModelData(const std::vector<Cell>& modelData, const QString debugInfo = QString());
   void clearStorage();

private:
   std::vector<std::pair<std::vector<Cell>, QString>> mModelStorage;
};
