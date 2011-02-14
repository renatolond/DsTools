#ifndef AABB_H
#define AABB_H

#include "tilemapcell.h"
#include "vectorrenderer.h"
#include "collidable.h"
#include "constants.h"
#include "spritecontroller.h"
#include "all_gfx.h"

template <class T>
        class AABB : public virtual Collidable<T>
{
    Vector2<T> pos;
    Vector2<T> oldPos;
    T xw;
    T yw;
    SpriteController spr;

public:
    VectorRenderer<T> *vr;
    AABB();
    ~AABB();
    AABB(Vector2<T> _pos, T _xw, T _yw);

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
AABB<T>::AABB()
{
}

template<class T>
AABB<T>::~AABB()
{
    spr.remove();
}

template<class T>
AABB<T>::AABB(Vector2<T> _pos, T _xw, T _yw)
{
    oldPos = pos = _pos;
    xw = _xw;
    yw = _yw;
    PA_LoadSpritePal(0, 0, (void *) square_Pal);
    spr.create((void *)(square_Sprite), OBJ_SIZE_16X16, 0);
    Draw();
}

template<class T>
void AABB<T>::Draw()
{
    spr.pos.x = (float)(pos.x-xw);
    spr.pos.y = (float)(pos.y-yw);
    spr.render();
    //vr->DrawAABB(pos.x-xw, pos.x+xw, pos.y-yw, pos.y+yw);
}

template<class T>
void AABB<T>::IntegrateVerlet()
{
    IntegrateVerletGeneric(*this);
}

template<class T>
void AABB<T>::getExt(T &_xw, T &_yw)
{
    _xw = xw;
    _yw = yw;
}

template<class T>
Vector2<T> AABB<T>::getPos()
{
    return pos;
}

template<class T>
Vector2<T> AABB<T>::getOldPos()
{
    return oldPos;
}

template<class T>
void AABB<T>::setPos(Vector2<T> p)
{
    pos = p;
}

template<class T>
void AABB<T>::setOldPos(Vector2<T> op)
{
    oldPos = op;
}

template<class T>
void AABB<T>::ReportCollisionVsWorld(T px, T py, T dx, T dy)
{
    ReportCollisionVsWorldGeneric(*this, px, py, dx, dy);
}

template<class T>
void AABB<T>::CollideVsWorldBounds()
{
    T x, y;

    x = screenMinX - (pos.x - xw);

    // collision against left side
    if ( x > 0 )
    {
        ReportCollisionVsWorld(x, 0, 1, 0);
    }
    else
    {
        x = pos.x + xw - screenMaxX;

        // collision against right side
        if ( x > 0 )
        {
            ReportCollisionVsWorld(-x, 0, -1, 0);
        }
    }

    y = screenMinY - (pos.y - yw);
    // collision against upper bounds
    if ( y > 0 )
    {
        ReportCollisionVsWorld(0, y, 0, 1);
    }
    else
    {
        y = pos.y + yw - screenMaxY;
        if ( y > 0 )
        {
            ReportCollisionVsWorld(0, -y, 0, -1);
        }
    }
}

template<class T>
void AABB<T>::CollideVsTile(TileMapCell<T> tile)
{
    T dx, dy;
    T x, y;

    dx = pos.x - tile.pos.x;
    x = tile.xw + xw - fabs(dx);

    if ( x > 0 )
    {
        dy = pos.y - tile.pos.y;
        y = tile.yw + yw - fabs(dy);

        if ( y > 0 )
        {
            if ( x < y )
            {
                if ( dx < 0 )
                {
                    x *= -1;
                    y = 0;
                }
                else
                    y = 0;
            }
            else
            {
                if ( dy < 0 )
                {
                    x = 0;
                    y *= -1;
                }
                else
                    x = 0;
            }

            tile.projAABB(x, y, *this);
            //ResolveBoxTile(x, y, *this, tile);
        }
    }
}

#endif // AABB_H
