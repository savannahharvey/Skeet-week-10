#pragma once
#include "order.h";
#include "bird.h";

/*********************************
 * ORDER FACTORY
 * The factory that creates orders for birds.
 ***********************************/
namespace OrderFactory 
{
   Order* createDrawOrder(Bird* bird);
   Order* createAdvanceOrder(Bird* bird);
};
