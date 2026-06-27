#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include "spawner.h"
#include "bird.h" 
namespace
{
   /***************************************************************/
   /***************************************************************/
   /*                             MISC.                           */
   /***************************************************************/
   /***************************************************************/


   /******************************************************************
    * RANDOM
    * These functions generate a random number.
    ****************************************************************/
   int randomInt(int min, int max)
   {
      assert(min < max);
      int num = (rand() % (max - min)) + min;
      assert(min <= num && num <= max);
      return num;
   }
}

/*********************************************
 * SPAWNER :: SPLIT INTO 8 DIGIT CHUNKS
 * Split the encoded spawn order into one code per bird.
 *********************************************/
std::vector<std::string> Spawner::splitInto8DigitChunks(const std::string& code)
{
   std::vector<std::string> chunks;

   for (size_t i = 0; i < code.size(); i += 8)
      chunks.push_back(code.substr(i, 8));

   return chunks;
}

/*********************************************
 * SPAWNER :: PARSE CHUNK
 * Parse a chunk of the encoded spawn order into spawn parameters.
 *********************************************/
bool Spawner::parseChunk(const std::string& chunk, SpawnParams& params)
{
   if (chunk.size() != 8)
      return false;

   if (!std::all_of(chunk.begin(), chunk.end(),
      [](unsigned char c)
      {
         return std::isdigit(c);
      }))
      return false;

   params.size = std::stoi(chunk.substr(0, 2));
   params.birdType = std::stoi(chunk.substr(2, 1));
   params.speed = std::stoi(chunk.substr(3, 2)) / 10.0;
   params.points = std::stoi(chunk.substr(5, 2));
   params.spawnRate = std::stoi(chunk.substr(7, 1));

   return params.spawnRate > 0;
}

/*********************************************
 * SPAWNER :: SHOULD SPAWN
 * Determine if a bird should spawn based on the spawn rate.
 *********************************************/
bool Spawner::shouldSpawn(int spawnRate)
{
   if (spawnRate <= 0)
      return false;

   return randomInt(0, spawnRate * 15) == 1;
}

/*********************************************
 * SPAWNER :: CREATE BIRD
 * Create a bird based on the spawn parameters.
 *********************************************/
Bird* Spawner::createBird(const SpawnParams& params)
{
   switch (params.birdType)
   {
   case 1:
      return new Standard(params.size, params.speed, params.points);
   case 2:
      return new Sinker(params.size, params.speed, params.points);
   case 3:
      return new Floater(params.size, params.speed, params.points);
   case 4:
      return new Crazy(params.size, params.speed, params.points);
   default:
      return nullptr;
   }
}

/*********************************************
 * SPAWNER :: SPAWN
 * Interpret the spawn order and return any birds that should spawn.
 *********************************************/
std::vector<Bird*> Spawner::spawn(const std::string& code)
{
   std::vector<Bird*> spawnedBirds;
   std::vector<std::string> chunks = splitInto8DigitChunks(code);

   for (const std::string& chunk : chunks)
   {
      SpawnParams params{};
      if (!parseChunk(chunk, params))
         continue;

      if (!shouldSpawn(params.spawnRate))
         continue;

      Bird* bird = createBird(params);
      if (bird != nullptr)
         spawnedBirds.push_back(bird);
   }

   return spawnedBirds;
}

