/***********************************************************************
 * Header File:
 *    SKEET
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The game class
 ************************************************************************/

#pragma once

#include "position.h"
#include "uiInteract.h"
#include "bird.h"
#include "bullet.h"
#include "effect.h"
#include "gun.h"
#include "time.h"
#include "score.h"
#include "points.h"
#include "order.h"

#include <list>

/*************************************************************************
 * Skeet
 * The game class
 *************************************************************************/
class Skeet
{
public:
    Skeet(Position & dimensions) : dimensions(dimensions),
        gun(Position(800.0, 0.0)), time(), score(), hitRatio(), bullseye(false) {}

    // handle all user input
    void interact(const UserInput& ui);

    // move the gameplay by one unit of time
    void animate();

    // output everything on the screen
    void drawLevel()  const;    // output the game
    void drawStatus() const;    // output the status information

    // is the game currently playing right now?
    bool isPlaying() const { return time.isPlaying();  }
private:
    // generate new birds
    void spawn();                  
    void drawBackground(double redBack, double greenBack, double blueBack) const;
    void drawTimer(double percent,
                   double redFore, double greenFore, double blueFore,
                   double redBack, double greenBack, double blueBack) const;
    void drawBullseye(double angle) const;

    template <typename T>
    void execute(void (*function)(T*), T* p) const; // handles Bird, Bullet (draw and kill), and Effect
    void execute(void (*function)(Bullet*, std::list<Effect*>&), Bullet* p, std::list<Effect*>& effects) const; // for moveBullet
    void execute(void (*function)(const Gun&), const Gun& gun) const;          // new

    Gun gun;                       // the gun
    std::list<Bird*> birds;        // all the shootable birds
    std::list<Bullet*> bullets;    // the bullets
    std::list<Effect*> effects;    // the fragments of a dead bird.
    std::list<Points>  points;     // point values;
    Time time;                     // how many frames have transpired since the beginning
    Score score;                   // the player's score
    HitRatio hitRatio;             // the hit ratio for the birds
    Position dimensions;           // size of the screen
    bool bullseye;
};
