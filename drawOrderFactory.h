#pragma once
#include "drawOrder.h";
#include "bird.h";

/*********************************
 * DRAW ORDER FACTORY
 * The factory that creates draw orders for birds.
 ***********************************/
static class DrawOrderFactory
{
   public:
    static DrawOrder* createDrawOrder(Bird* bird);
};