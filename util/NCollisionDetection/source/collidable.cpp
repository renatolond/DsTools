#include "collidable.h"

void ReportCollisionVsWorldGeneric(Collidable<double> &c, double px, double py, double dx, double dy)
{
//    PA_OutputText(1, 0, 0, "Colliding vs world...");
    Vector2<double> pos, oldPos;
    double xw, yw, vx, vy;
    double temp, nx, ny, tx, ty;
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

void IntegrateVerletGeneric(Collidable<double> &c)
{
    Vector2<double> pos, oldPos, newPos, d;
    Vector2<double> iPos, iOldPos;

    pos.x = c.getPos().x;
    pos.y = c.getPos().y;
    oldPos.x = c.getOldPos().x;
    oldPos.y = c.getOldPos().y;
    d = pos*drag - oldPos * drag;
    d.y += gravity;
    newPos = pos + (pos * drag - oldPos * drag);
    newPos.y += gravity;

//    PA_OutputText(1, 0, 1, "d: %d %d           ", (int)d.x, (int)d.y);
//    PA_OutputText(1, 0, 2, "New pos: %d %d           ", (int)newPos.x, (int)newPos.y);
//    PA_OutputText(1, 0, 3, "Old pos: %d %d           ", (int)pos.x, (int)pos.y);

    iPos.x = newPos.x;
    iPos.y = newPos.y;

    iOldPos.x = pos.x;
    iOldPos.y = pos.y;

    c.setPos(iPos);
    c.setOldPos(iOldPos);
}
