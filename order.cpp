#include "order.h"
#include "random.h"
#include <cassert>
#include "position.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

/* DRAW ORDERS */

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void DrawBirdOrder::drawDisk(const Position& center, double radius,
   double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
      glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
      glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}

/*********************************************
 * STANDARD DRAW
 * Draw a standard bird: blue center and white outline
 *********************************************/
void DrawStandardOrder::execute()
{
   if (!receiver->isDead())
   {
      drawDisk(receiver->getPosition(), receiver->getRadius() - 0.0, 1.0, 1.0, 1.0); // white outline
      drawDisk(receiver->getPosition(), receiver->getRadius() - 3.0, 0.0, 0.0, 1.0); // blue center
   }
}

/*********************************************
 * FLOATER DRAW
 * Draw a floating bird: white center and blue outline
 *********************************************/
void DrawFloaterOrder::execute()
{
   if (!receiver->isDead())
   {
      drawDisk(receiver->getPosition(), receiver->getRadius() - 0.0, 0.0, 0.0, 1.0); // blue outline
      drawDisk(receiver->getPosition(), receiver->getRadius() - 4.0, 1.0, 1.0, 1.0); // white center
   }
}

/*********************************************
 * CRAZY DRAW
 * Draw a crazy bird: concentric circles in a course gradient
 *********************************************/
void DrawCrazyOrder::execute()
{
   if (!receiver->isDead())
   {
      drawDisk(receiver->getPosition(), receiver->getRadius() * 1.0, 0.0, 0.0, 1.0); // bright blue outside
      drawDisk(receiver->getPosition(), receiver->getRadius() * 0.8, 0.2, 0.2, 1.0);
      drawDisk(receiver->getPosition(), receiver->getRadius() * 0.6, 0.4, 0.4, 1.0);
      drawDisk(receiver->getPosition(), receiver->getRadius() * 0.4, 0.6, 0.6, 1.0);
      drawDisk(receiver->getPosition(), receiver->getRadius() * 0.2, 0.8, 0.8, 1.0); // almost white inside
   }
}

/*********************************************
 * SINKER DRAW
 * Draw a sinker bird: black center and dark blue outline
 *********************************************/
void DrawSinkerOrder::execute()
{
   if (!receiver->isDead())
   {
      drawDisk(receiver->getPosition(), receiver->getRadius() - 0.0, 0.0, 0.0, 0.8);
      drawDisk(receiver->getPosition(), receiver->getRadius() - 4.0, 0.0, 0.0, 0.0);
   }
}

/* ADVANCE ORDERS */

/*********************************************
 * ADVANCE STANDARD ORDER
 * How the standard bird moves - inertia and drag
 *********************************************/
void AdvanceStandardOrder::execute()
{
   // small amount of drag
   Velocity newVel = receiver->getVelocity();
   newVel *= 0.995;
   (*receiver) = newVel;

   // inertia
   Position newPos = receiver->getPosition();
   newPos.add(newVel);
   (*receiver) = newPos;

   // out of bounds checker
   if (receiver->isOutOfBounds())
   {
      receiver->kill();
      int newPoints = receiver->getPoints();
      newPoints *= -1; // points go negative when it is missed!
      receiver->setPoints(newPoints);
   }
}

/*********************************************
 * ADVANCE SINKER ORDER
 * How the sinker bird moves: no drag but gravity
 *********************************************/
void AdvanceSinkerOrder::execute()
{
   // gravity
   Velocity newVel = receiver->getVelocity();
   newVel.addDy(-0.07);
   (*receiver) = newVel;

   // inertia
   Position newPos = receiver->getPosition();
   newPos.add(newVel);
   (*receiver) = newPos;

   // out of bounds checker
   if (receiver->isOutOfBounds())
   {
      receiver->kill();
      int newPoints = receiver->getPoints();
      newPoints *= -1; // points go negative when it is missed!
      receiver->setPoints(newPoints);
   }
}

/*********************************************
 * ADVANCE CRAZY ORDER
 * How the crazy bird moves: every half a second it changes direction
 *********************************************/
void AdvanceCrazyOrder::execute()
{
   Velocity newVel = receiver->getVelocity();

   // erratic turns every half a second or so
   if (Random::randomInt(0, 15) == 0)
   {
      newVel.addDy(Random::randomFloat(-1.5, 1.5));
      newVel.addDx(Random::randomFloat(-1.5, 1.5));
   }

   // update velocity
   (*receiver) = newVel;

   // inertia
   Position newPos = receiver->getPosition();
   newPos.add(newVel);
   (*receiver) = newPos;

   // out of bounds checker
   if (receiver->isOutOfBounds())
   {
      receiver->kill();
      int newPoints = receiver->getPoints();
      newPoints *= -1; // points go negative when it is missed!
      receiver->setPoints(newPoints);
   }
}

/*********************************************
 * ADVANCE FLOATER ORDER
 * How the floating bird moves: strong drag and anti-gravity
 *********************************************/
void AdvanceFloaterOrder::execute()
{
   Velocity newVel = receiver->getVelocity();

   // large amount of drag
   newVel *= 0.990;

   // inertia 
   Position newPos = receiver->getPosition();
   newPos.add(newVel);
   (*receiver) = newPos;

   // anti-gravity
   newVel.addDy(0.05);
   (*receiver) = newVel;

   // out of bounds checker
   if (receiver->isOutOfBounds())
   {
      receiver->kill();
      int newPoints = receiver->getPoints();
      newPoints *= -1; // points go negative when it is missed!
      receiver->setPoints(newPoints);
   }
}