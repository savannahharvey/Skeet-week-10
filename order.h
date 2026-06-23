#pragma once
#include "bird.h"

/*********************************
* ORDER
* The abstract order class.
*********************************/
class Order
{
public:
   void virtual execute() = 0;
};

/* DRAW ORDERS */

/*********************************
 * DRAW ORDER
 * The shared interface for all concrete draw orders.
 *********************************/
class DrawBirdOrder : public Order
{
public:
   DrawBirdOrder(Bird* bird) : receiver(bird) {}
protected:
   Bird* receiver;
   void drawDisk(const Position& center, double radius,
                 double red, double green, double blue);
};

/*********************************
* DRAW STANDARD ORDER
* The concrete order that draws standard birds.
**********************************/
class DrawStandardOrder : public DrawBirdOrder
{
public:
   DrawStandardOrder(Bird* bird) : DrawBirdOrder(bird) {}
   void execute() override;
};

/*********************************
* DRAW SINKER ORDER
* The concrete order that draws sinker birds.
***********************************/
class DrawSinkerOrder : public DrawBirdOrder
{
public:
   DrawSinkerOrder(Bird* bird) : DrawBirdOrder(bird) {}
   void execute() override;
};

/*********************************
* DRAW CRAZY ORDER
* The concrete order that draws crazy birds.
***********************************/
class DrawCrazyOrder : public DrawBirdOrder
{
public:
   DrawCrazyOrder(Bird* bird) : DrawBirdOrder(bird) {}
   void execute() override;
};

/*********************************
* DRAW FLOATER ORDER
* The concrete order that draws floater birds.
***********************************/
class DrawFloaterOrder : public DrawBirdOrder
{
public:
   DrawFloaterOrder(Bird* bird) : DrawBirdOrder(bird) {}
   void execute() override;
};

/* ADVANCE ORDERS */

/*********************************
 * ADVANCE ORDER
 * The shared interface for all concrete advance orders.
 *********************************/
class AdvanceBirdOrder : public Order
{
public:
   AdvanceBirdOrder(Bird* bird) : receiver(bird) {}
protected:
   Bird* receiver;
};

/*********************************
* ADVANCE STANDARD ORDER
* The concrete order that advances standard birds.
**********************************/
class AdvanceStandardOrder : public AdvanceBirdOrder
{
public:
   AdvanceStandardOrder(Bird* bird) : AdvanceBirdOrder(bird) {}
   void execute() override;
};

/*********************************
* ADVANCE SINKER ORDER
* The concrete order that advances sinker birds.
**********************************/
class AdvanceSinkerOrder : public AdvanceBirdOrder
{
public:
   AdvanceSinkerOrder(Bird* bird) : AdvanceBirdOrder(bird) {}
   void execute() override;
};

/*********************************
* ADVANCE CRAZY ORDER
* The concrete order that advances crazy birds.
**********************************/
class AdvanceCrazyOrder : public AdvanceBirdOrder
{
public:
   AdvanceCrazyOrder(Bird* bird) : AdvanceBirdOrder(bird) {}
   void execute() override;
};

/*********************************
* ADVANCE FLOATER ORDER
* The concrete order that advances floater birds.
**********************************/
class AdvanceFloaterOrder : public AdvanceBirdOrder
{
public:
   AdvanceFloaterOrder(Bird* bird) : AdvanceBirdOrder(bird) {}
   void execute() override;
};