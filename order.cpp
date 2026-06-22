#include "order.h"

 /************************
  * DRAW BIRD ORDER EXECUTE
  * Execute the draw order on the bird receiver.
  ************************/
void DrawBirdOrder::execute()
{
   if (receiver)
      receiver->draw();
}

/************************
 * ADVANCE BIRD ORDER EXECUTE
 * Execute the advance order on the bird receiver.
 ************************/
void AdvanceBirdOrder::execute()
{
   if (receiver)
      receiver->advance();
}
