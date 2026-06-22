/**********************************************************************
 * Executor
 **********************************************************************/

#include "executor.h"

 /************************
  * EXECUTOR EXECUTE
  * Execute the provided order.
  ************************/
void Executor::execute(Order& order) const
{
   order.execute();
}
