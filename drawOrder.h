#pragma once
#include "bird.h"

/*********************************
* DRAW ORDER
* The abstract order class.
*********************************/
class DrawOrder
{
public:
   DrawOrder(Bird* bird) : receiver(bird) {}
   virtual void execute() = 0;
protected:
   Bird* receiver;
   void drawDisk(const Position& center, double radius,
      double red, double green, double blue);
};

/*********************************
* DRAW STANDARD ORDER
* The concrete order that draws standard birds.
**********************************/
class DrawStandardOrder : public DrawOrder
{
public:
   DrawStandardOrder(Bird* bird) : DrawOrder(bird) {}
   void execute() override;
};

/*********************************
* DRAW SINKER ORDER
* The concrete order that draws sinker birds.
***********************************/
class DrawSinkerOrder : public DrawOrder
{
   public:
   DrawSinkerOrder(Bird* bird) : DrawOrder(bird) {}
   void execute() override;
};

/*********************************
* DRAW CRAZY ORDER
* The concrete order that draws crazy birds.
***********************************/
class DrawCrazyOrder : public DrawOrder
{
   public:
   DrawCrazyOrder(Bird* bird) : DrawOrder(bird) {}
   void execute() override;
};

/*********************************
* DRAW FLOATER ORDER
* The concrete order that draws floater birds.
***********************************/
class DrawFloaterOrder : public DrawOrder
{
   public:
   DrawFloaterOrder(Bird* bird) : DrawOrder(bird) {}
   void execute() override;
};