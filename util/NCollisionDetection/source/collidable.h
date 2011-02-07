#ifndef COLLIDABLE_H
#define COLLIDABLE_H

//#include "tilemapcell.h"
//#include "aabb.h"
#include "vector2.h"

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

void ReportCollisionVsWorldGeneric(Collidable<int> &c, double px, double py, double dx, double dy)
{
    PA_OutputText(1, 0, 0, "Colliding vs world...");
    Vector2<int> pos, oldPos;
    int xw, yw, vx, vy;
    int temp, nx, ny, tx, ty;
    double fx, fy, bx, by;
    pos = c.getPos();
    oldPos = c.getOldPos();
    c.getExt(xw, yw);

    vx = pos.x - oldPos.x;
    vy = pos.y - oldPos.y;

    temp = vx*dx + vy*dy;
    nx = temp*dx;
    ny = temp*dy;

    tx = vx - nx;
    ty = vy - ny;

    if ( temp < 0 )
    {
        fx = tx * friction;
        fy = ty * friction;

        bx = nx * (bounce+1.0);
        by = ny * (bounce+1.0);
    }
    else
    {
        fx = fy = bx = by = 0;
    }

    pos.x += px;
    pos.y += py;
    oldPos.x += px + bx + fx;
    oldPos.y += py + by + fy;
    c.setPos(pos);
    c.setOldPos(oldPos);
}

void IntegrateVerletGeneric(Collidable<int> &c)
{
    Vector2<double> pos, oldPos, newPos, d;
    Vector2<int> iPos, iOldPos;

    pos.x = c.getPos().x;
    pos.y = c.getPos().y;
    oldPos.x = c.getOldPos().x;
    oldPos.y = c.getOldPos().y;
    d = pos*drag - oldPos * drag;
    d.y += gravity;
    newPos = pos + (pos * drag - oldPos * drag);
    newPos.y += gravity;

    PA_OutputText(1, 0, 1, "d: %d %d           ", (int)d.x, (int)d.y);
    PA_OutputText(1, 0, 2, "New pos: %d %d           ", (int)newPos.x, (int)newPos.y);
    PA_OutputText(1, 0, 3, "Old pos: %d %d           ", (int)pos.x, (int)pos.y);

    iPos.x = newPos.x;
    iPos.y = newPos.y;

    iOldPos.x = pos.x;
    iOldPos.y = pos.y;

    c.setPos(iPos);
    c.setOldPos(iOldPos);
}

//template <class T>
//void ResolveBoxTile(T x, T y, Collidable<T>& c, TileMapCell<T> tile)
//{
//}


#endif // COLLIDABLE_H
