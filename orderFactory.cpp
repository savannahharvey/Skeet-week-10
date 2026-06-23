#include "orderFactory.h"

Order* OrderFactory::createDrawOrder(Bird* bird)
{
    if (bird->getType() == "Standard")
    {
        return new DrawStandardOrder(bird);
    }
    else if (bird->getType() == "Sinker")
    {
        return new DrawSinkerOrder(bird);
    }
    else if (bird->getType() == "Crazy")
    {
        return new DrawCrazyOrder(bird);
    }
    else if (bird->getType() == "Floater")
    {
        return new DrawFloaterOrder(bird);
    }
}

Order* OrderFactory::createAdvanceOrder(Bird* bird)
{
   std::string type = bird->getType();

   if (type == "Standard") 
      return new AdvanceStandardOrder(bird);
   if (type == "Sinker")   
      return new AdvanceSinkerOrder(bird);
   if (type == "Crazy")    
      return new AdvanceCrazyOrder(bird);
   if (type == "Floater")  
      return new AdvanceFloaterOrder(bird);

   return nullptr;
}