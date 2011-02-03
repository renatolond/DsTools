#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "tilemapcell.h"

template <class T>
class Collidable
{
    virtual void Draw()=0;
    virtual void Verlet()=0;
    virtual void ReportCollisionVsWorld()=0;
    virtual void CollideVsWorldBounds()=0;
    virtual void CollideVsTile(TileMapCell<T> tile)=0;
};

#endif // COLLIDABLE_H
