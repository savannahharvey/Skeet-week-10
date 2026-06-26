#pragma once

#include "skeet.h"

// new
// draw commands

void drawEffect(Effect* p);
void drawBullet(Bullet* p);
void drawBird(Bird* p);
void drawGun(const Gun& gun);

// move commands
void moveEffect(Effect* p);
void moveBullet(Bullet* p, std::list<Effect*>& effects);
void moveBird(Bird* p);

// kill commands
void killBullet(Bullet* p);
void killBird(Bird* p);