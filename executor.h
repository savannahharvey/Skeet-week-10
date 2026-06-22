/***********************************************************************
 *    Executor for encapsulated invocation orders
 ************************************************************************/

#pragma once

#include "order.h"

 /*************************************************************************
  * Executor
  * Invokes an order object.
  *************************************************************************/
class Executor
{
public:
   void execute(Order& order) const;
};
