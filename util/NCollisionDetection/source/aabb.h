#ifndef AABB_H
#define AABB_H

#include "tilemapcell.h"
#include "collidable.h"

template <class T>
        class AABB : public virtual Collidable<T>
{
    Vector2<T> pos;
    T xw;
    T yw;

public:
    AABB();
    void CollidevsTile(TileMapCell<T> tile);
};

template<class T>
AABB<T>::AABB()
{
}

template<class T>
void AABB<T>::CollidevsTile(TileMapCell<T> tile)
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
