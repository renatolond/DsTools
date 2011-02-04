#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "tilemapcell.h"

template <class T>
class Collidable
{
    virtual void Draw()=0;
    virtual void Verlet()=0;
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

        bx = nx * (bounce+1);
        by = ny * (bounce+1);
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

#endif // COLLIDABLE_H
