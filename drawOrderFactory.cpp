#include "drawOrderFactory.h"

DrawOrder* DrawOrderFactory::createDrawOrder(Bird* bird)
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