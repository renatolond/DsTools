#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>
#include <sstream>
#include <cmath>

#define eps 0.0001

template <class T>
class Vector2
{
public:
    T x;
    T y;
    Vector2();
    Vector2(T a, T b);
    std::string ToString();
    Vector2<T> operator +(const Vector2<T> &b) const;
    Vector2<T> operator -(const Vector2<T> &b) const;
    Vector2<T> normR();
    Vector2<T> dir();
    Vector2<T> proj(const Vector2<T> &b);
    double projLen(const Vector2<T> &b);
    T dot (const Vector2<T> &b);
    T cross (const Vector2<T> &b);
    double len ();
    Vector2<T>& operator *=(const double b);
    Vector2<T> operator *(const double &b) const;
    void normalize();
    Vector2<T>& operator +=(const Vector2<T> &b);
    Vector2<T>& operator -=(const Vector2<T> &b);
};

template <class T>
Vector2<T>::Vector2()
{
}

template <class T>
Vector2<T>::Vector2(T a, T b)
{
    x = a;
    y = b;
}

template <class T>
std::string Vector2<T>::ToString()
{
    std::ostringstream outs;

    outs << "(" << this->x << "," << this->y << ")";

    return outs.str();
}

template <class T>
Vector2<T> Vector2<T>::operator +(const Vector2<T> &b) const
{
    Vector2<T> temp(this->x + b.x, this->y + b.y);
    return temp;
}

template <class T>
Vector2<T> Vector2<T>::operator -(const Vector2<T> &b) const
{
    Vector2<T> temp(this->x - b.x, this->y - b.y);

    return temp;
}

template <class T>
Vector2<T> Vector2<T>::normR()
{
    Vector2<T> temp(this->y*-1, this->x);

    return temp;
}

template <class T>
Vector2<T> Vector2<T>::dir()
{
    Vector2 temp(this);
    temp.normalize();

    return temp;
}

template <class T>
Vector2<T> Vector2<T>::proj(const Vector2<T> &b)
{
    Vector2 a(b);
    T temp = a.dot(a);
    Vector2<T> ret;

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

template <class T>
double Vector2<T>::projLen(const Vector2<T> &b)
{
    Vector2 a(b);
    T temp = a.dot(a);

    if ( fabs(temp) < eps )
    {
        return 0.0f;
    }

    return fabs(this->dot(a)/temp);
}

template <class T>
T Vector2<T>::dot (const Vector2<T> &b)
{
    return (this->x*b.x + this->y*b.y);
}

template <class T>
T Vector2<T>::cross (const Vector2<T> &b)
{
    return (this->x*b.x - this->y*b.y);
}

template <class T>
double Vector2<T>::len ()
{
    return sqrt(this->x*this->x + this->y*this->y);
}

template <class T>
Vector2<T>& Vector2<T>::operator *=(const double b)
{
   this->x *= b;
   this->y *= b;
   return *this;
}

template <class T>
Vector2<T> Vector2<T>::operator *(const double &b) const
{
    Vector2<T> temp(this->x*b, this->x*b);
    return temp;
}

template <class T>
void Vector2<T>::normalize()
{
    double temp = this->len();
    if ( fabs(temp) > eps )
    {
        this->x /= temp;
        this->y /= temp;
    }
}

template <class T>
Vector2<T>& Vector2<T>::operator +=(const Vector2<T> &b)
{
    this->x += b.x;
    this->y += b.y;

    return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator -=(const Vector2<T> &b)
{
    this->x -= b.x;
    this->y -= b.y;

    return *this;
}

#endif // VECTOR2_H
