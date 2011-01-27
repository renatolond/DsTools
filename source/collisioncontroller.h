#ifndef COLLISIONCONTROLLER_H
#define COLLISIONCONTROLLER_H

#include <PA9.h>

#include "all_gfx.h"
#include "spritecontroller.h"
#include "playercontroller.h"

class CollisionController
{
    PlayerController *player;
public:
    CollisionController();
    void checkForCollisions(const int &scroll);
    void addCollideableSprite(SpriteController *s);
    void addCollideablePlayer(PlayerController *p);
    bool isCollideable(s16 tile);
};

#endif // COLLISIONCONTROLLER_H
