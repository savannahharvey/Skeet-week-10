/***********************************************************************
 * Source File:
 *    SPAWNER
 * Summary:
 *    Interprets encoded bird spawn orders and creates birds.
 ************************************************************************/

#include "spawner.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
using namespace std;

/*********************************************
 * RANDOM
 * Generate a random integer in the range [min, max).
 *********************************************/
static int randomInt(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num < max);

   return num;
}

/*********************************************
 * SPAWNER :: SPLIT INTO 8 DIGIT CHUNKS
 * Split the encoded spawn order into one code per bird.
 *********************************************/
vector<string> Spawner::splitInto8DigitChunks(const string& code)
{
   vector<string> chunks;

   for (int end = (int)code.length(); end > 0; end -= 8)
   {
      int start = max(0, end - 8);
      chunks.push_back(code.substr(start, end - start));
   }

   return chunks;
}

/*********************************************
 * SPAWNER :: SPAWN
 * Interpret the spawn order and return any birds that should spawn.
 *********************************************/
list<Bird*> Spawner::spawn(const string& code)
{
   list<Bird*> spawnedBirds;
   vector<string> chunks = splitInto8DigitChunks(code);

   for (const string& chunk : chunks)
   {
      if (chunk.length() != 8)
         continue;

      bool hasNonDigit = false;
      for (char digit : chunk)
         if (!isdigit((unsigned char)digit))
            hasNonDigit = true;
      if (hasNonDigit)
         continue;

      int size = stoi(chunk.substr(0, 2));
      int birdType = stoi(chunk.substr(2, 1));
      double speed = stod(chunk.substr(3, 2)) / 10.0;
      int points = stoi(chunk.substr(5, 2));
      int spawnRate = stoi(chunk.substr(7, 1));

      if (spawnRate <= 0)
         continue;

      if (randomInt(0, spawnRate * 15) != 1)
         continue;

      switch (birdType)
      {
      case 1:
         spawnedBirds.push_back(new Standard(size, speed, points));
         break;
      case 2:
         spawnedBirds.push_back(new Sinker(size, speed, points));
         break;
      case 3:
         spawnedBirds.push_back(new Floater(size, speed, points));
         break;
      case 4:
         spawnedBirds.push_back(new Crazy(size, speed, points));
         break;
      default:
         break;
      }
   }

   return spawnedBirds;
}
