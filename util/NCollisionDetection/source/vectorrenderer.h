#ifndef VECTORRENDERER_H
#define VECTORRENDERER_H

#include "vector2.h"
#include <vector>
#include <PA9.h>
#include "constants.h"

template <class T>
        class VectorRenderer
{
    int colorFG;
    int thickness;
public:
    VectorRenderer();
    void Clear();
    void SetStyle(int thickness, int rgb, int alpha);
    void StartFill(T x, T y, int rgb, int alpha);
    void StopFill();
    void DrawLine(const Vector2<T> &v0, const Vector2<T> &v1);
    void DrawLine(T x0, T y0, T x1, T y1);
    void DrawLineStrip(std::vector< Vector2<T> > vList);
    void DrawTri(const Vector2<T> &v0, const Vector2<T> &v1, const Vector2<T> &v2);
    void DrawTri(T x0, T y0, T x1, T y1, T x2, T y2);
    void DrawQuad(const Vector2<T> &v0, const Vector2<T> &v1, const Vector2<T> &v2, const Vector2<T> &v3);
    void DrawQuad(T x0, T y0, T x1, T y1, T x2, T y2, T x3, T x4);
    void DrawPlus(const Vector2<T> &v);
    void DrawPlus(T x0, T y0);
    void DrawPlus(const Vector2<T> &v, T r);
    void DrawPlus(T x0, T y0, T r);
    void DrawCross(const Vector2<T> &v);
    void DrawCross(T x0, T y0);
    void DrawCross(const Vector2<T> &v, T r);
    void DrawCross(T x0, T y0, T r);
    void DrawCircle(const Vector2<T> &v, T r);
    void DrawCircle(T x0, T y0, T r);
    void DrawArc(const Vector2<T> &v0, const Vector2<T> &v1, const Vector2<T> r);
    void DrawArc(T x0, T y0, T x1, T y1, T rx, T ry);
    void DrawAABB(const Vector2<T> &v, T wx, T wy);
    void DrawAABB(T minX, T maxX, T minY, T maxY);
    void DrawConcaveCCWArc(T cx, T cy, T px, T py);
    void DrawConcaveCCWArc(const Vector2<T> &c, const Vector2<T> &p);
};

template <class T>
        VectorRenderer<T>::VectorRenderer()
{
    PA_Init16bitDblBuffer(0, 3);
    //PA_Init16bitBg(0, 5);
    colorFG = 0xFFFF;
    thickness = 1;
}

template <class T>
        void VectorRenderer<T>::Clear()
{
    PA_Clear16bitBg(0);
}

template <class T>
        void VectorRenderer<T>::SetStyle(int thick, int rgb, int alpha)
{
    thickness = thick;
    int r, g, b;
    r = g = b = rgb;
    r = r >> (2*8);
    g = (g >> (8)) - (r << 8);
    b = b - (g << 8) - (r << (2*8));
    colorFG = alpha;
    colorFG <<= 5;
    colorFG += b >> 3;
    colorFG <<= 5;
    colorFG += g >> 3;
    colorFG <<= 5;
    colorFG += r >> 3;
}

template <class T>
        void VectorRenderer<T>::StartFill(T x, T y, int rgb, int alpha)
{
}

template <class T>
        void VectorRenderer<T>::StopFill()
{

}

template <class T>
        inline void VectorRenderer<T>::DrawLine(const Vector2<T> &v0, const Vector2<T> &v1)
{
    DrawLine(v0.x, v0.y, v1.x, v1.y);
}

template <class T>
        void VectorRenderer<T>::DrawLine(T x0, T y0, T x1, T y1)
{
    if ( x0 < 0 || x0 > screenSizeX )
        return;
    if ( x1 < 0 || x1 > screenSizeX )
        return;
    if ( y0 < 0 || y0 > screenSizeY )
        return;
    if ( y1 < 0 || y1 > screenSizeY )
        return;

    PA_Draw16bitLineEx(0, x0, y0, x1, y1, colorFG, thickness);
}

template <class T>
        void VectorRenderer<T>::DrawLineStrip(std::vector< Vector2<T> > vList)
{
    if ( vList.size() < 2 )
        return;
    for ( int i = 0 ; i < (int)vList.size() -1 ; i++ )
    {
        DrawLine(vList[i], vList[i+1]);
    }

}

template <class T>
        inline void VectorRenderer<T>::DrawTri(const Vector2<T> &v0, const Vector2<T> &v1, const Vector2<T> &v2)
{
    DrawTri(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y);
}

template <class T>
        void VectorRenderer<T>::DrawTri(T x0, T y0, T x1, T y1, T x2, T y2)
{
    DrawLine(x0, y0, x1, y1);
    DrawLine(x1, y1, x2, y2);
    DrawLine(x2, y2, x0, y0);
}

template <class T>
        inline void VectorRenderer<T>::DrawQuad(const Vector2<T> &v0, const Vector2<T> &v1, const Vector2<T> &v2, const Vector2<T> &v3)
{
    DrawQuad(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
}

template <class T>
        void VectorRenderer<T>::DrawQuad(T x0, T y0, T x1, T y1, T x2, T y2, T x3, T y3)
{
    DrawLine(x0, y0, x1, y1);
    DrawLine(x1, y1, x2, y2);
    DrawLine(x2, y2, x3, y3);
    DrawLine(x3, y3, x0, y0);
}

template <class T>
        inline void VectorRenderer<T>::DrawPlus(const Vector2<T> &v)
{
    DrawPlus(v.x, v.y, 1);
}

template <class T>
        inline void VectorRenderer<T>::DrawPlus(T x0, T y0)
{
    DrawPlus(x0, y0, 1);
}

template <class T>
        inline void VectorRenderer<T>::DrawPlus(const Vector2<T> &v, T r)
{
    DrawPlus(v.x, v.y, r);
}

template <class T>
        void VectorRenderer<T>::DrawPlus(T x0, T y0, T r)
{
    DrawLine(x0-r, y0, x0+r, y0);
    DrawLine(x0, y0-r, x0, y0+r);
}

template <class T>
        inline void VectorRenderer<T>::DrawCross(const Vector2<T> &v)
{
    DrawCross(v.x, v.y, 1);
}

template <class T>
        inline void VectorRenderer<T>::DrawCross(T x0, T y0)
{
    DrawCross(x0, y0, 1);
}

template <class T>
        inline void VectorRenderer<T>::DrawCross(const Vector2<T> &v, T r)
{
    DrawCross(v.x, v.y, r);
}

template <class T>
        void VectorRenderer<T>::DrawCross(T x0, T y0, T r)
{
    DrawLine(x0-r, y0-r, x0+r, y0+r);
    DrawLine(x0+r, y0-r, x0-r, y0+r);
}

template <class T>
        inline void VectorRenderer<T>::DrawCircle(const Vector2<T> &v, T r)
{
    DrawCircle(v.x, v.y, r);
}

template <class T>
        void VectorRenderer<T>::DrawCircle(T x0, T y0, T r)
{
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;

    while (x <= y){
        DrawLine(x0 + x, y0 + y, x0 + x, y0 + y);
        DrawLine(x0 - x, y0 + y, x0 - x, y0 + y);
        DrawLine(x0 + x, y0 - y, x0 + x, y0 - y);
        DrawLine(x0 - x, y0 - y, x0 - x, y0 - y);
        DrawLine(x0 + y, y0 + x, x0 + y, y0 + x);
        DrawLine(x0 - y, y0 + x, x0 - y, y0 + x);
        DrawLine(x0 + y, y0 - x, x0 + y, y0 - x);
        DrawLine(x0 - y, y0 - x, x0 - y, y0 - x);
        if (p < 0) p += 4 * x++ + 6;
        else p += 4 * (x++ - y--) + 10;
    }
}

template <class T>
        inline void VectorRenderer<T>::DrawArc(const Vector2<T> &v0, const Vector2<T> &v1, const Vector2<T> r)
{
    DrawArc(v0.x, v0.y, v1.x, v1.y, r.x, r.y);
}

template <class T>
        void lerp (Vector2<T> &dest, const T &x0, const T &y0, const T &x1, const T &y1, float t)
{
    dest.x = x0 + (x1-x0)*t;
    dest.y = y0 + (y1-y0)*t;
}
// from http://www.cubic.org/docs/bezier.htm
template <class T>
        void VectorRenderer<T>::DrawArc(T x0, T y0, T x1, T y1, T rx, T ry)
{
    Vector2<T> p0, p;
    p0.x = x0;
    p0.y = y0;
    for ( int i=0; i<1000; i++ )
    {
        double t = (double)i/999.0;
        Vector2<T> ab,bc,cd;
        lerp (ab, x0, y0, rx, ry ,t);
        lerp (bc, rx, ry, x1, y1, t);
        lerp (p, ab.x, ab.y, bc.x, bc.y, t);
        DrawLine(p0, p);
        p0 = p;
    }
}

template <class T>
        void VectorRenderer<T>::DrawAABB(const Vector2<T> &v, T wx, T wy)
{
    DrawAABB(v.x-wx, v.x+wx, v.y-wy, v.y+wy);
}

template <class T>
        void VectorRenderer<T>::DrawAABB(T minX, T maxX, T minY, T maxY)
{
    DrawQuad(maxX, maxY, minX, maxY, minX, minY, maxX, minY);
}

template <class T>
        void VectorRenderer<T>::DrawConcaveCCWArc(const Vector2<T> &c, const Vector2<T> &p)
{
    DrawConcaveCCWArc(c.x, c.y, p.x, p.y);
}

template <class T>
        void VectorRenderer<T>::DrawConcaveCCWArc(T cx, T cy, T px, T py)
{
    Vector2<double> c, p0, v, p1, n, c0;
    double clen;
    p0.x = px;
    p0.y = py;
    c.x = cx;
    c.y = cy;

    v = p0 - c;
    n.x = v.y;
    n.y = -v.x;

    p1 = p0 + n - c;
    p1.normalize();
    p1 *= v.len();
    p1 += c;

    c0 = (p0 + p1) * 0.5 - c;

    clen = c0.len();

    c0.normalize();
    c0 *= v.len() + (v.len() - clen);
    c0 += c;

    DrawArc(p0.x, p0.y, p1.x, p1.y, c0.x, c0.y);

    p0 = p1;

    v = p0 - c;
    n.x = v.y;
    n.y = -v.x;

    p1 = p0 + n - c;
    p1.normalize();
    p1 *= v.len();
    p1 += c;

    c0 = (p0 + p1) * 0.5 - c;

    clen = c0.len();

    c0.normalize();
    c0 *= v.len() + (v.len() - clen);
    c0 += c;

    DrawArc(p0.x, p0.y, p1.x, p1.y, c0.x, c0.y);
}

#endif // VECTORRENDERER_H
