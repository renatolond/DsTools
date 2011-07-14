#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>
#include <sstream>
#include <cmath>

//#include "constants.h"
extern double eps;

typedef int tVectorReturn;

class Vector2
{
public:
    tVectorReturn x;
    tVectorReturn y;
    Vector2();
    Vector2(tVectorReturn a, tVectorReturn b);
    std::string ToString();
    Vector2 operator +(const Vector2 &b) const;
    Vector2 operator -(const Vector2 &b) const;
    Vector2 operator -(const tVectorReturn &b) const;
    Vector2 normR();
    Vector2 dir();
    Vector2 proj(const Vector2 &b);
    double projLen(const Vector2 &b);
    tVectorReturn dot (const Vector2 &b);
    tVectorReturn cross (const Vector2 &b);
    double len ();
    Vector2& operator *=(const double b);
    Vector2 operator *(const double &b) const;
    void normalize();
    Vector2& operator +=(const Vector2 &b);
    Vector2& operator -=(const Vector2 &b);
};

#endif // VECTOR2_H
