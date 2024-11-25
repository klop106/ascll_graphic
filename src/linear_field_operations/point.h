#ifndef POINT
#define POINT

#include "vector.h"

struct Point
{
    double x;
    double y;
    double z;

    Point(const double _x, const double _y, const double _z) : x(_x), y(_y), z(_z) {};
    Point() : x(0.), y(0.), z(0.) {};

    Point operator=(const Point _point);

    Point operator+(const Vector3 _other) const { return Point(x + _other.x, y + _other.y, z + _other.z); }
    Point operator+=(const Vector3 _other) const { return operator+(_other); }

    Vector3 operator-(const Point _other) const { return Vector3(x - _other.x, y - _other.y, z - _other.z); }

    void show();
};
#endif