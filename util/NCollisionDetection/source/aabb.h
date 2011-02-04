#ifndef AABB_H
#define AABB_H

#include "tilemapcell.h"
#include "collidable.h"
#include "constants.h"

template <class T>
        class AABB : public virtual Collidable<T>
{
    Vector2<T> pos;
    Vector2<T> oldPos;
    T xw;
    T yw;
public:
    AABB();

    Vector2<T> getPos();
    Vector2<T> getOldPos();
    void setPos(Vector2<T> p);
    void setOldPos(Vector2<T> op);
    void CollideVsTile(TileMapCell<T> tile);
    void CollideVsWorldBounds();
    void ReportCollisionVsWorld(T px, T py, T dx, T dy);
};

template<class T>
AABB<T>::AABB()
{
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
    ReportCollisionVsWorldGeneric(px, py, dx, dy);
}

template<class T>
void AABB<T>::CollideVsWorldBounds()
{
    int x, y;

    x = screenMinX - (pos.x - xw);

    // collision against left side
    if ( x > 0 )
    {
        ReportCollisionVsWorld(x, 0, 1, 0);
    }
    else
    {
        x = pos.x + xw - screenSizeX;

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
        y = pos.y + yw - screenSizeY;
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
    x = tile.xw + xw - abs(dx);

    if ( x > 0 )
    {
        dy = pos.y - tile.pos.y;
        y = tile.yw + yw - abs(dy);

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

            ResolveBoxTile(x, y, *this, tile);
        }
    }
}

#endif // AABB_H
