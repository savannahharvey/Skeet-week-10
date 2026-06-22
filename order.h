/***********************************************************************
 * Header File:
 *    ORDER
 ************************************************************************/

#pragma once

#include "bird.h"

 /*************************************************************************
  * Order
  * The abstract command/order interface
  *************************************************************************/
class Order
{
public:
   virtual ~Order() {}
   virtual void execute() = 0;
};

/*************************************************************************
 * DrawBirdOrder
 * Concrete order that draws a bird receiver
 *************************************************************************/
class DrawBirdOrder : public Order
{
public:
   DrawBirdOrder(Bird* receiver) : receiver(receiver) {}
   void execute() override;

private:
   Bird* receiver;
};

/*************************************************************************
 * AdvanceBirdOrder
 * Concrete order that advances a bird receiver
 *************************************************************************/
class AdvanceBirdOrder : public Order
{
public:
   AdvanceBirdOrder(Bird* receiver) : receiver(receiver) {}
   void execute() override;

private:
   Bird* receiver;
};
