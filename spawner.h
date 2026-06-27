#pragma once

#include <string>
#include <vector>

class Bird;

class Spawner
{
public:
   static std::vector<Bird*> spawn(const std::string& code);

private:
   Spawner() = delete;
   struct SpawnParams
   {
      int size;
      int birdType;
      double speed;
      int points;
      int spawnRate;
   };

   static bool parseChunk(const std::string& chunk, SpawnParams& params);
   static bool shouldSpawn(int spawnRate);
   static Bird* createBird(const SpawnParams& params);
   static std::vector<std::string> splitInto8DigitChunks(const std::string& code);
};

