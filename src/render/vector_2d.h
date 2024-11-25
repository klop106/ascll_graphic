#ifndef VECTOR2
#define VECTOR2

#include <stdio.h>
#include <iostream>
#include <cmath>

#include "../linear_field_operations/point.h"
#include "../linear_field_operations/vector.h"

struct Vector2
{
    private:
        double norm_cash;

    public:
        double u;
        double v;

        Vector2() : u(0.), v(0.) { calc_norm(); }
        Vector2(const double _u, const double _v);

        Vector2 operator+(const Vector2 _other) const { return Vector2(u + _other.u, v + _other.v); }
        Vector2 operator-(const Vector2 _other) const { return Vector2(u - _other.u, v - _other.v); }
        Vector2 operator*(const Vector2 _other) const { return Vector2(u * _other.u, v * _other.v); }
        Vector2 operator/(const Vector2 _other) const { return Vector2(u / _other.u, v / _other.v); }

        void calc_norm() { norm_cash = sqrt(u * u + v * v); }
        double norm() const { return norm_cash; }

        double scalar_poduct(const Vector2 _other) const { return (u * _other.u + v * _other.v); }

        Point generate_3d_point(const Vector3 _ort_x, const Vector3 _ort_y, const Point _ref_point);
};
#endif