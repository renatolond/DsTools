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

void ReportCollisionVsWorldGeneric(Collidable<myint> &c, myint px, myint py, myint dx, myint dy)
{
//    PA_OutputText(1, 0, 0, "Colliding vs world...");
    Vector2<myint> pos, oldPos;
    myint xw, yw, vx, vy;
    myint temp, nx, ny, tx, ty;
    myint fx, fy, bx, by;
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

        fx = tx - (friction*(tx/100));
        fy = ty - (friction*(ty/100));

        bx = nx + (bounce*(nx/100));
        by = ny + (bounce*(ny/100));
    }
    else
    {
        fx = fy = bx = by = 0;
    }

//    char message[1024];

//    sprintf(message,"x %d, y %d",(int)pos.x, (int)pos.y);
//    nocashMessage(message);
//    sprintf(message,"x %ld, y %ld",pos.x, pos.y);
//    nocashMessage(message);
//    sprintf(message,"tx %ld, ty %ld",tx, ty);
//    nocashMessage(message);
//    sprintf(message,"vx %ld, vy %ld",tx, ty);
//    nocashMessage(message);
//    sprintf(message,"temp %ld, nx %ld, ny %ld",temp, nx, ny);
//    nocashMessage(message);
//    sprintf(message,"bx %ld, by %ld, fx %ld, fy %ld",bx,by,fx,fy);
//    nocashMessage(message);
    //asm("mov r11,r11");

    //PA_OutputText(1, 0, 17, "bx %d, by %d, fx %d, fy %d    ",bx,by,fx,fy);

    pos.x += px;
    pos.y += py;

    oldPos.x += px + bx + fx;
    oldPos.y += py + by + fy;

    c.setPos(pos);
    c.setOldPos(oldPos);
}

void IntegrateVerletGeneric(Collidable<myint> &c)
{
    Vector2<myint> pos, oldPos, newPos;
    Vector2<myint> iPos, iOldPos;

    pos = c.getPos();
    oldPos = c.getOldPos();

    newPos.x = pos.x + ((pos.x-(drag*(pos.x/100))) - (oldPos.x-(drag*(oldPos.x/100))));
    newPos.y = pos.y + ((pos.y-(drag*(pos.y/100))) - (oldPos.y-(drag*(oldPos.y/100))));
    newPos.y += gravity;

    iPos.x = newPos.x;
    iPos.y = newPos.y;

    iOldPos.x = pos.x;
    iOldPos.y = pos.y;

    c.setPos(iPos);
    c.setOldPos(iOldPos);
}

void IntegrateVerletGeneric(Collidable<double> &c)
{
    Vector2<double> pos, oldPos, newPos;
    Vector2<double> iPos, iOldPos;

    pos.x = c.getPos().x;
    pos.y = c.getPos().y;
    oldPos.x = c.getOldPos().x;
    oldPos.y = c.getOldPos().y;

    newPos = pos + (pos * drag - oldPos * drag);
    newPos.y += gravity;

    iPos.x = newPos.x;
    iPos.y = newPos.y;

    iOldPos.x = pos.x;
    iOldPos.y = pos.y;

    c.setPos(iPos);
    c.setOldPos(iOldPos);
}
