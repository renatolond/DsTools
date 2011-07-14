#include "vector2.h"

double eps = 0.0001;

Vector2::Vector2()
{
}

Vector2::Vector2(tVectorReturn a, tVectorReturn b)
{
    x = a;
    y = b;
}

std::string Vector2::ToString()
{
    std::ostringstream outs;

    outs << "(" << this->x << "," << this->y << ")";

    return outs.str();
}

Vector2 Vector2::operator +(const Vector2 &b) const
{
    Vector2 temp(this->x + b.x, this->y + b.y);
    return temp;
}

Vector2 Vector2::operator -(const Vector2 &b) const
{
    Vector2 temp(this->x - b.x, this->y - b.y);

    return temp;
}

Vector2 Vector2::operator -(const tVectorReturn &b) const
{
    Vector2 temp(this->x - b, this->y - b);

    return temp;
}

Vector2 Vector2::normR()
{
    Vector2 temp(this->y*-1, this->x);

    return temp;
}

Vector2 Vector2::dir()
{
    Vector2 temp(*this);
    temp.normalize();

    return temp;
}

Vector2 Vector2::proj(const Vector2 &b)
{
    Vector2 a(b);
    tVectorReturn temp = a.dot(a);
    Vector2 ret;

    if ( fabs(temp) < eps )
    {
        ret = Vector2(*this);
    }
    else
    {
        ret = Vector2(b);
        ret *= this->dot(a) / temp;
    }

    return ret;
}

double Vector2::projLen(const Vector2 &b)
{
    Vector2 a(b);
    tVectorReturn temp = a.dot(a);

    if ( fabs(temp) < eps )
    {
        return 0.0f;
    }

    return fabs(this->dot(a)/temp);
}

tVectorReturn Vector2::dot (const Vector2 &b)
{
    return (this->x*b.x + this->y*b.y);
}

tVectorReturn Vector2::cross (const Vector2 &b)
{
    return (this->x*b.x - this->y*b.y);
}

double Vector2::len ()
{
    return sqrt(this->x*this->x + this->y*this->y);
}

Vector2& Vector2::operator *=(const double b)
{
   this->x *= b;
   this->y *= b;
   return *this;
}

Vector2 Vector2::operator *(const double &b) const
{
    Vector2 temp(this->x*b, this->y*b);
    return temp;
}

void Vector2::normalize()
{
    double temp = this->len();
    if ( fabs(temp) > eps )
    {
        this->x /= temp;
        this->y /= temp;
    }
}

Vector2& Vector2::operator +=(const Vector2 &b)
{
    this->x += b.x;
    this->y += b.y;

    return *this;
}

Vector2& Vector2::operator -=(const Vector2 &b)
{
    this->x -= b.x;
    this->y -= b.y;

    return *this;
}


