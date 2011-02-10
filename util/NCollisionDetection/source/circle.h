#ifndef CIRCLE_H
#define CIRCLE_H

#include "tilemapcell.h"
#include "vectorrenderer.h"
#include "collidable.h"
#include "constants.h"
#include "spritecontroller.h"
#include "all_gfx.h"

template <class T>
        class Circle : public virtual Collidable<T>
{
    Vector2<T> pos;
    Vector2<T> oldPos;
    //T xw;
    //T yw;
    T r;
    SpriteController spr;

public:
    VectorRenderer<T> *vr;
    Circle();
    Circle(Vector2<T> _pos, T r);
    ~Circle();

    Vector2<T> getPos();
    Vector2<T> getOldPos();
    void setPos(Vector2<T> p);
    void setOldPos(Vector2<T> op);
    void IntegrateVerlet();
    void CollideVsTile(TileMapCell<T> tile);
    void CollideVsWorldBounds();
    void ReportCollisionVsWorld(T px, T py, T dx, T dy);
    void Draw();
    void getExt(T &_xw, T &_yw);
};

template<class T>
Circle<T>::Circle()
{
    oldPos = pos = Vector2<T>(0, 0);
    r = 8;

    PA_LoadSpritePal(0, 2, (void *) circle_Pal);
    spr.init(0, 2);
    spr.create((void *)(circle_Sprite), OBJ_SIZE_16X16, 2);
}

template<class T>
Circle<T>::~Circle()
{
    spr.remove();
}

template<class T>
Circle<T>::Circle(Vector2<T> _pos, T _r)
{
    oldPos = pos = _pos;
    r = _r;
    PA_LoadSpritePal(0, 2, (void *) circle_Pal);
    spr.init(0, 2);
    spr.create((void *)(circle_Sprite), OBJ_SIZE_16X16, 2);
    Draw();
}

template<class T>
void Circle<T>::Draw()
{
    spr.pos.x = (float)(pos.x-r);
    spr.pos.y = (float)(pos.y-r);
    spr.render();
}

template<class T>
void Circle<T>::IntegrateVerlet()
{
    IntegrateVerletGeneric(*this);
}

template<class T>
void Circle<T>::getExt(T &_xw, T &_yw)
{
    _xw = r;
    _yw = r;
}

template<class T>
Vector2<T> Circle<T>::getPos()
{
    return pos;
}

template<class T>
Vector2<T> Circle<T>::getOldPos()
{
    return oldPos;
}

template<class T>
void Circle<T>::setPos(Vector2<T> p)
{
    pos = p;
}

template<class T>
void Circle<T>::setOldPos(Vector2<T> op)
{
    oldPos = op;
}

template<class T>
void Circle<T>::ReportCollisionVsWorld(T px, T py, T dx, T dy)
{
    ReportCollisionVsWorldGeneric(*this, px, py, dx, dy);
}

template<class T>
void Circle<T>::CollideVsWorldBounds()
{
    T x, y;

    x = screenMinX - (pos.x - r);
    if ( x > 0 )
    {
        ReportCollisionVsWorld(x, 0, 1, 0);
    }
    else
    {
        x = pos.x + r - screenMaxX;
        if ( x > 0 )
        {
            ReportCollisionVsWorld(-x, 0, -1, 0);
        }
    }

    y = screenMinY - (pos.y - r);
    if ( y > 0 )
    {
        ReportCollisionVsWorld(0, y, 0, 1);
    }
    else
    {
        y = pos.y + r - screenMaxY;
        if ( y > 0 )
        {
            ReportCollisionVsWorld(0, -y, 0, -1);
        }
    }
}

template<class T>
void Circle<T>::CollideVsTile(TileMapCell<T> tile)
{
    T px, py;
    T cx, cy;

    cx = pos.x - tile.pos.x;
    px = tile.xw + r - fabs(cx);
    if ( px > 0 )
    {
        cy = pos.y - tile.pos.y;
        py = tile.yw + r - fabs(cy);
        if ( py > 0 )
        {
            T oh, ov;

            oh = ov = 0;

            if ( cx < -tile.xw )
                oh = -1;
            else if ( tile.xw < cx )
                oh = 1;

            if ( cy < -tile.yw )
                ov = -1;
            else if ( tile.yw < cy )
                ov = 1;

            tile.projCircle(px, py, oh, ov, *this);
        }
    }
}


#endif // CIRCLE_H
