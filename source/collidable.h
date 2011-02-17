#ifndef COLLIDABLE_H
#define COLLIDABLE_H

//#include "tilemapcell.h"
//#include "aabb.h"
#include "vector2.h"
#include "constants.h"

#include <PA9.h>

template <class T>
        class TileMapCell;

template <class T>
class Collidable
{
public:
    virtual void Draw()=0;
    virtual void IntegrateVerlet()=0;
    virtual void ReportCollisionVsWorld(T px, T py, T dx, T dy)=0;
    virtual void CollideVsWorldBounds()=0;
    virtual void CollideVsTile(TileMapCell<T> tile)=0;
    virtual Vector2<T> getPos()=0;
    virtual Vector2<T> getOldPos()=0;
    virtual void setPos(Vector2<T> p)=0;
    virtual void setOldPos(Vector2<T> op)=0;
    virtual void getExt(T &xw, T &yw)=0;
};

void ReportCollisionVsWorldGeneric(Collidable<double> &c, double px, double py, double dx, double dy);
void ReportCollisionVsWorldGeneric(Collidable<mytype> &c, mytype px, mytype py, mytype dx, mytype dy);
void IntegrateVerletGeneric(Collidable<mytype> &c);
void IntegrateVerletGeneric(Collidable<double> &c);

//template <class T>
//void ResolveBoxTile(T x, T y, Collidable<T>& c, TileMapCell<T> tile)
//{
//}


#endif // COLLIDABLE_H
