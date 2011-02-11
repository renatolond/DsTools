#ifndef COLLISIONCONTROLLER_H
#define COLLISIONCONTROLLER_H

#include <PA9.h>

#include "all_gfx.h"
#include "spritecontroller.h"
#include "tilemapcell.h"
#include "playercontroller.h"

class CollisionController
{
    PlayerController<double> *player;
    TileMapCell<double> **map;
public:
    CollisionController();
    void checkForCollisions(const int &scroll);
    void addCollideableSprite(SpriteController *s);
    void addCollideablePlayer(PlayerController<double> *p);
    bool isCollideable(s16 tile);
    void loadTileMap();
};

#endif // COLLISIONCONTROLLER_H
