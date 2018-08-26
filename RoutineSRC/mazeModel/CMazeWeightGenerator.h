#pragma once

#include <vector>
#include <QString>
#include <QFile>

class CMazeWeightGenerator
{
public:
   explicit CMazeWeightGenerator(const uint8_t sizeX, const uint8_t sizeY);

   bool generateRandomWeightInRange(const uint8_t from, const uint8_t to);
   std::vector<uint8_t>& getWeightStorage();
   bool updateWeightsFromStorageFile();
   bool updateWeightOnPosition(uint16_t position, uint8_t weight);

private:
   std::vector<uint8_t> mWeightStorage;
   QFile mFile;
   uint8_t mSizeX;
   uint8_t mSizeY;
};
