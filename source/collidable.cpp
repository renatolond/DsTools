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

void ReportCollisionVsWorldGeneric(Collidable<mytype> &c, mytype px, mytype py, mytype dx, mytype dy)
{
//    PA_OutputText(1, 0, 0, "Colliding vs world...");
    Vector2<mytype> pos, oldPos;
    mytype xw, yw, vx, vy;
    mytype temp, nx, ny, tx, ty;
    mytype fx, fy, bx, by;
//    double dfx, dfy, dbx, dby;
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
        fx = (tx*friction)/100;
        fy = (ty*friction)/100;


        bx = nx*(bounce+100)/100;
        by = ny*(bounce+100)/100;

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
//    sprintf(message,"tx %d, ty %d",tx, ty);
//    nocashMessage(message);
//    sprintf(message,"vx %ld, vy %ld",tx, ty);
//    nocashMessage(message);
//    sprintf(message,"temp %ld, nx %ld, ny %ld",temp, nx, ny);
//    nocashMessage(message);
//    sprintf(message,"bx %d, by %d, fx %d, fy %d",bx,by,fx,fy);
//    nocashMessage(message);
//    sprintf(message,"============");
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

void IntegrateVerletGeneric(Collidable<mytype> &c)
{
    Vector2<mytype> pos, oldPos, newPos;
    Vector2<mytype> iPos, iOldPos;

    pos = c.getPos();
    oldPos = c.getOldPos();

    newPos.x = pos.x + ((mytype)((pos.x*drag)/100) - (mytype)((oldPos.x*drag)/100));
    newPos.y = pos.y + ((mytype)((pos.y*drag)/100) - (mytype)((oldPos.y*drag)/100));
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
