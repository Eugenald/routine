#include <QCoreApplication>
#include <QDebug>
#include "CMazeWeightGenerator.h"
#include "CMazeModel.h"

const QString FILEPATH = ":/maze/mazeCellWeights";

CMazeWeightGenerator::CMazeWeightGenerator(const uint8_t sizeX, const uint8_t sizeY)
   : mFile(FILEPATH)
   , mSizeX(sizeX)
   , mSizeY(sizeY)
{
   mWeightStorage.reserve(mSizeX * mSizeY);
}

bool CMazeWeightGenerator::generateRandomWeightInRange(const uint8_t from, const uint8_t to)
{
   bool success = mFile.open(QIODevice::ReadWrite);

   if (success)
   {
       QTextStream stream( &mFile );

       /*for (int i = 0; i < mSizeX * mSizeY)
       {
          stream << "something" << endl;
       }*/

   }

   mFile.close();

   return success;
}

std::vector<uint8_t>& CMazeWeightGenerator::getWeightStorage()
{
   return mWeightStorage;
}

bool CMazeWeightGenerator::updateWeightsFromStorageFile()
{
   return true;
}

bool CMazeWeightGenerator::updateWeightOnPosition(uint16_t position, uint8_t weight)
{
   return true;
}
