/***********************************************************************
 * Header File:
 *    SPAWNER
 * Summary:
 *    Interprets encoded bird spawn orders and creates birds.
 ************************************************************************/

#pragma once

#include "bird.h"
#include <list>
#include <string>
#include <vector>

 /*********************************************
  * SPAWNER
  * Interprets encoded spawn commands.
  *********************************************/
class Spawner
{
public:
   static std::list<Bird*> spawn(const std::string& code);

private:
   static std::vector<std::string> splitInto8DigitChunks(const std::string& code);
};
