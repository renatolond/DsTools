#ifndef TILEMAPCELL_H
#define TILEMAPCELL_H

#include "vector2.h"
#include "aabb.h"
#include "all_gfx.h"

#define SQRT2 1.414214E+000
#define SQRT5 2.236068E+000

namespace TileEnum
{
    enum TileID
    {
        empty,
        full,

        _45degPN,
        _45degNN,
        _45degNP,
        _45degPP,

        concavePN,
        concaveNN,
        concaveNP,
        concavePP,

        convexPN,
        convexNN,
        convexNP,
        convexPP,

        _22degPNs,
        _22degNNs,
        _22degNPs,
        _22degPPs,

        _22degPNb,
        _22degNNb,
        _22degNPb,
        _22degPPb,

        _67degPNs,
        _67degNNs,
        _67degNPs,
        _67degPPs,

        _67degPNb,
        _67degNNb,
        _67degNPb,
        _67degPPb,

        halfD,
        halfR,
        halfU,
        halfL

    };
}

namespace CTypeEnum
{
    enum CType
    {
        _empty = TileEnum::empty,
        _full = TileEnum::full,
        _45deg = TileEnum::_45degPN,
        concave = TileEnum::concavePN,
        convex = TileEnum::convexPN,
        _22degs = TileEnum::_22degPNs,
        _22degb = TileEnum::_22degPNb,
        _67degs = TileEnum::_67degPNs,
        _67degb = TileEnum::_67degPNb,
        half = TileEnum::halfD
           };
}

template <class T>
        class TileMapCell
{
    int signx;
    int signy;
    double sx;
    double sy;

    TileEnum::TileID id;
    CTypeEnum::CType ctype;
    SpriteController s;
public:
    Vector2<T> pos;
    T xw;
    T yw;

    TileMapCell();
    TileMapCell(T x, T y, T xW, T yW);
    void SetState(TileEnum::TileID ID);
    void Clear();
    void UpdateType();
    void Draw();
    void projAABB(T x, T y, AABB<T>& aabb);
    void projAABBFull(T x, T y, AABB<T>& aabb);
    void projAABB45deg(T x, T y, AABB<T>& aabb);
    void projAABBConcave(T x, T y, AABB<T>& aabb);
    void projAABBConvex(T x, T y, AABB<T>& aabb);
    void projAABB22degS(T x, T y, AABB<T>& aabb);
    void projAABB22degB(T x, T y, AABB<T>& aabb);
    void projAABB67degS(T x, T y, AABB<T>& aabb);
    void projAABB67degB(T x, T y, AABB<T>& aabb);
    void projAABBHalf(T x, T y, AABB<T>& aabb);
    T minX();
    T maxX();
    T minY();
    T maxY();
};

template <class T>
        TileMapCell<T>::TileMapCell()
{

}


template <class T>
        TileMapCell<T>::TileMapCell(T x, T y, T xW, T yW)
{
    pos = Vector2<T>(x, y);
    xw = xW;
    yw = yW;
    id = TileEnum::empty;
    ctype = CTypeEnum::_empty;

    PA_LoadSpritePal(0, 2, (void *)tiles_Pal);
    s.init(0, 1);
    s.create((void*)tiles_Sprite, OBJ_SIZE_16X16, 2);
    s.addAnimation(0,0,0);
    s.addAnimation(1,1,0);
    s.addAnimation(2,2,0);
    s.addAnimation(3,3,0);
    s.addAnimation(4,4,0);
    s.addAnimation(5,5,0);
    s.addAnimation(6,6,0);
    s.addAnimation(7,7,0);
    s.addAnimation(8,8,0);
}

template <class T>
        void TileMapCell<T>::projAABBFull(T x, T y, AABB<T>& aabb)
{
    double temp;
    temp = sqrt(x*x + y*y);
    aabb.ReportCollisionVsWorld(x, y, x/temp, y/temp);
}

template <class T>
        void TileMapCell<T>::projAABB45deg(T x, T y, AABB<T>& aabb)
{
    T ox, oy;
    T aabbxw, aabbyw;
    aabb.getExt(aabbxw, aabbyw);
    ox = aabb.getPos().x - signx * aabbxw - pos.x;
    oy = aabb.getPos().y - signy * aabbyw - pos.y;

    T dp = ox * sx + oy * sy;
    if ( dp < 0 )
    {
        T ssx, ssy;
        ssx = sx*-dp;
        ssy = sy*-dp;

        T lenN, lenP;
        lenN = sqrt(ssx*ssx + ssy*ssy);
        lenP = sqrt(x*x + y*y);

        if ( lenP < lenN )
        {
            aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
        }
        else
        {
            aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
        }
    }
}

template <class T>
        void TileMapCell<T>::projAABBConcave(T x, T y, AABB<T>& aabb)
{
    T ox, oy, twid;
    T aabbxw, aabbyw;
    aabb.getExt(aabbxw, aabbyw);
    ox = pos.x + signx * xw - (aabb.getPos().x - signx * aabbxw);
    oy = pos.y + signy * yw - (aabb.getPos().y - signy * aabbyw);
    twid = xw * 2;

    T len = sqrt(ox*ox+oy*oy);
    T pen = len - twid;
    if ( pen > 0 )
    {
        T lenP = sqrt(x*x + y*y);

        if ( lenP < pen )
        {
            aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
        }
        else
        {
            ox = ox / len;
            oy = oy / len;
            aabb.ReportCollisionVsWorld(ox * pen, oy * pen, ox, oy);
        }
    }
}

template <class T>
        void TileMapCell<T>::projAABBConvex(T x, T y, AABB<T>& aabb)
{
    T ox, oy, twid;
    T aabbxw, aabbyw;
    aabb.getExt(aabbxw, aabbyw);
    ox = aabb.getPos().x - signx * aabbxw - (pos.x - signx * xw);
    oy = aabb.getPos().y - signy * aabbyw - (pos.y - signy * yw);
    twid = xw * 2;

    T len = sqrt(ox*ox+oy*oy);
    T pen = twid - len;
    if ( signx * ox < 0 || signy * oy < 0 )
    {
        T lenP = sqrt(x*x + y*y);
        aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
    }
    else if ( pen > 0 )
    {
        ox = ox / len;
        oy = oy / len;
        aabb.ReportCollisionVsWorld(ox * pen, oy * pen, ox, oy);
    }
}

template <class T>
        void TileMapCell<T>::projAABB22degS(T x, T y, AABB<T>& aabb)
{
    T py;
    T aabbxw, aabbyw;
    aabb.getExt(aabbxw, aabbyw);

    py = aabb.getPos().y - signy * aabbyw;

    T cy = pos.y - py;

    if ( cy*signy > 0 )
    {
        T ox, oy;
        ox = aabb.getPos().x - signx * aabbxw - (pos.x + signx*xw);
        oy = aabb.getPos().y - signy * aabbyw - (pos.y - signy*yw);

        T dp = ox * sx + oy * sy;
        if ( dp < 0 )
        {
            T ssx, ssy;
            ssx = sx*-dp;
            ssy = sy*-dp;

            T lenN, lenP;
            lenN = sqrt(ssx*ssx + ssy*ssy);
            lenP = sqrt(x*x + y*y);

            T ay = fabs(cy);

            if ( lenP < lenN )
            {
                if ( ay < lenP )
                    aabb.ReportCollisionVsWorld(0, cy, 0, cy/ay);
                else
                    aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
            }
            else
            {
                if ( ay < lenN )
                    aabb.ReportCollisionVsWorld(0, cy, 0, cy/ay);
                else
                    aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
            }
        }
    }
}

template <class T>
        void TileMapCell<T>::projAABB22degB(T x, T y, AABB<T>& aabb)
{
    T aabbxw, aabbyw;
    aabb.getExt(aabbxw, aabbyw);

    T ox, oy;
    ox = aabb.getPos().x - signx * aabbxw - (pos.x - signx*xw);
    oy = aabb.getPos().y - signy * aabbyw - (pos.y + signy*yw);

    T dp = ox * sx + oy * sy;
    if ( dp < 0 )
    {
        T ssx, ssy;
        ssx = sx*-dp;
        ssy = sy*-dp;

        T lenN, lenP;
        lenN = sqrt(ssx*ssx + ssy*ssy);
        lenP = sqrt(x*x + y*y);


        if ( lenP < lenN )
        {
            aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
        }
        else
        {
            aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
        }
    }
}

template <class T>
        void TileMapCell<T>::projAABB67degS(T x, T y, AABB<T>& aabb)
{
    T px;
    T aabbxw, aabbyw;
    aabb.getExt(aabbxw, aabbyw);

    px = aabb.getPos().x - signx * aabbxw;

    T cx = pos.x - px;

    if ( cx*signx > 0 )
    {
        T ox, oy;
        ox = aabb.getPos().x - signx * aabbxw - (pos.x - signx*xw);
        oy = aabb.getPos().y - signy * aabbyw - (pos.y + signy*yw);

        T dp = ox * sx + oy * sy;
        if ( dp < 0 )
        {
            T ssx, ssy;
            ssx = sx*-dp;
            ssy = sy*-dp;

            T lenN, lenP;
            lenN = sqrt(ssx*ssx + ssy*ssy);
            lenP = sqrt(x*x + y*y);

            T ax = fabs(cx);

            if ( lenP < lenN )
            {
                if ( ax < lenP )
                    aabb.ReportCollisionVsWorld(cx, 0, cx/ax, 0);
                else
                    aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
            }
            else
            {
                if ( ax < lenN )
                    aabb.ReportCollisionVsWorld(cx, 0, cx/ax, 0);
                else
                    aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
            }
        }
    }
}

template <class T>
        void TileMapCell<T>::projAABB67degB(T x, T y, AABB<T>& aabb)
{

}

template <class T>
        void TileMapCell<T>::projAABBHalf(T x, T y, AABB<T>& aabb)
{

}


template <class T>
        void TileMapCell<T>::projAABB(T x, T y, AABB<T>& aabb)
{
    if ( ctype == CTypeEnum::_full )
        projAABBFull(x, y, aabb);
    if ( ctype == CTypeEnum::_45deg )
        projAABB45deg(x, y, aabb);
    if ( ctype == CTypeEnum::concave )
        projAABBConcave(x, y, aabb);
    if ( ctype == CTypeEnum::convex )
        projAABBConvex(x, y, aabb);
    if ( ctype == CTypeEnum::_22degs )
        projAABB22degS(x, y, aabb);
    if ( ctype == CTypeEnum::_22degb )
        projAABB22degB(x, y, aabb);
    if ( ctype == CTypeEnum::_67degs )
        projAABB67degS(x, y, aabb);
}

template <class T>
        T TileMapCell<T>::minX()
{
    return pos.x - xw;
}

template <class T>
        T TileMapCell<T>::maxX()
{
    return pos.x + xw;
}

template <class T>
        T TileMapCell<T>::minY()
{
    return pos.y - yw;
}

template <class T>
        T TileMapCell<T>::maxY()
{
    return pos.y + yw;
}

template <class T>
        void TileMapCell<T>::SetState(TileEnum::TileID ID)
{
    if ( ID == TileEnum::empty )
    {
        Clear();
        return;
    }

    id = ID;
    UpdateType();
    Draw();
}


// Useless function?
template <class T>
        void TileMapCell<T>::Clear()
{
    id = TileEnum::empty;
    UpdateType();
    Draw();
}

template <class T>
        void TileMapCell<T>::UpdateType()
{
    // Defining sign in x and y
    if ( id == TileEnum::_45degNN || id == TileEnum::concaveNN || id == TileEnum::convexNN || id == TileEnum::_22degNNb ||
         id == TileEnum::_22degNNs || id == TileEnum::_67degNNb || id == TileEnum::_67degNNs )
    {
        signx = signy = -1;
    }
    else if ( id == TileEnum::_45degNP || id == TileEnum::concaveNP || id == TileEnum::convexNP || id == TileEnum::_22degNPb ||
              id == TileEnum::_22degNPs || id == TileEnum::_67degNPb || id == TileEnum::_67degNPs )
    {
        signx = -1;
        signy = 1;
    }
    else if ( id == TileEnum::_45degPN || id == TileEnum::concavePN || id == TileEnum::convexPN || id == TileEnum::_22degPNb ||
              id == TileEnum::_22degPNs || id == TileEnum::_67degPNb || id == TileEnum::_67degPNs )
    {
        signx = 1;
        signy = -1;
    }
    else if ( id == TileEnum::_45degPP || id == TileEnum::concavePP || id == TileEnum::convexPP || id == TileEnum::_22degPPb ||
              id == TileEnum::_22degPPs || id == TileEnum::_67degPPb || id == TileEnum::_67degPPs )
    {
        signx = signy = 1;
    }


    if ( id == TileEnum::full )
    {
        ctype = CTypeEnum::_full;
        signx = signy = sx = sy = 0;
    }
    else if ( id == TileEnum::_45degNN || id == TileEnum::_45degNP || id == TileEnum::_45degPN || id == TileEnum::_45degPP )
    {
        ctype = CTypeEnum::_45deg;
        sx = signx / SQRT2;
        sy = signy / SQRT2;
    }
    else if ( id == TileEnum::concaveNN || id == TileEnum::concaveNP || id == TileEnum::concavePN || id == TileEnum::concavePP )
    {
        ctype = CTypeEnum::concave;
        sx = sy = 0;
    }
    else if ( id == TileEnum::convexNN || id == TileEnum::convexNP || id == TileEnum::convexPN || id == TileEnum::convexPP )
    {
        ctype = CTypeEnum::convex;
        sx = sy = 0;
    }
    else if ( id == TileEnum::_22degNNb || id == TileEnum::_22degNPb || id == TileEnum::_22degPNb || id == TileEnum::_22degPPb )
    {
        ctype = CTypeEnum::_22degb;
        sx = signx / SQRT5;
        sy = signy*2 / SQRT5;
    }
    else if ( id == TileEnum::_22degNNs || id == TileEnum::_22degNPs || id == TileEnum::_22degPNs || id == TileEnum::_22degPPs )
    {
        ctype = CTypeEnum::_22degs;
        sx = signx / SQRT5;
        sy = signy*2 / SQRT5;
    }
    else if ( id == TileEnum::_67degNNb || id == TileEnum::_67degNPb || id == TileEnum::_67degPNb || id == TileEnum::_67degPPb )
    {
        ctype = CTypeEnum::_67degb;
        sx = signx*2 / SQRT5;
        sy = signy / SQRT5;
    }
    else if ( id == TileEnum::_67degNNs || id == TileEnum::_67degNPs || id == TileEnum::_67degPNs || id == TileEnum::_67degPPs )
    {
        ctype = CTypeEnum::_67degs;
        sx = signx*2 / SQRT5;
        sy = signy / SQRT5;
    }
    else if ( id == TileEnum::halfD || id == TileEnum::halfL || id == TileEnum::halfR || id == TileEnum::halfU )
    {
        if ( id == TileEnum::halfD )
        {
            signx = 0;
            signy = -1;
        }
        else if ( id == TileEnum::halfU )
        {
            signx = 0;
            signy = 1;
        }
        else if ( id == TileEnum::halfL )
        {
            signx = 1;
            signy = 0;
        }
        else if ( id == TileEnum::halfR )
        {
            signx = -1;
            signy = 0;
        }

        sx = signx;
        sy = signy;
    }
    else if ( id == TileEnum::empty )
    {
        ctype = CTypeEnum::_empty;
        signx = signy = sx = sy = 0;
    }
    else
    {
        // TODO: Wrong id. Show error message.
        // Trace Bad Tile.
    }
}

template <class T>
        void TileMapCell<T>::Draw()
{
    s.pos.x = (float)(pos.x-xw);
    s.pos.y = (float)(pos.y-yw);

    if ( ctype == CTypeEnum::_full )
        s.beginAnimation(0);
    if ( ctype == CTypeEnum::_45deg )
        s.beginAnimation(1);
    if ( ctype == CTypeEnum::concave )
        s.beginAnimation(2);
    if ( ctype == CTypeEnum::convex )
        s.beginAnimation(3);
    if ( ctype == CTypeEnum::_22degs )
        s.beginAnimation(4);
    if ( ctype == CTypeEnum::_22degb )
        s.beginAnimation(5);
    if ( ctype == CTypeEnum::_67degs )
        s.beginAnimation(6);
    // GotoAndStop(id+1) ?
    s.render();
}

#endif // TILEMAPCELL_H
