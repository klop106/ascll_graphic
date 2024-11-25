#ifndef VECTOR3
#define VECTOR3

#include <stdio.h>
#include <iostream>
#include <cmath>

struct Vector3
{
    private:
        double norm_cash;

        void calc_norm() { norm_cash = sqrt(x * x + y * y + z * z); }

    public:
        double x;
        double y;
        double z;

        Vector3() : x(0.), y(0.), z(0.) { calc_norm(); }
        Vector3(const double _x, const double _y, const double _z) : x(_x), y(_y), z(_z) { calc_norm(); }
        //Vector3(const double _r, const angle _phi, const angle _psi) : {}

        Vector3 operator=(const Vector3 _other);

        Vector3 operator+(const Vector3 _other) const { return Vector3(x + _other.x, y + _other.y, z + _other.z); }
        Vector3 operator-(const Vector3 _other) const { return Vector3(x - _other.x, y - _other.y, z - _other.z); }
        Vector3 operator*(const Vector3 _other) const { return Vector3(x * _other.x, y * _other.y, z * _other.z); }
        Vector3 operator*(const double lamda) const { return Vector3(x * lamda, y * lamda, z * lamda); }
        Vector3 operator/(const Vector3 _other) const { return Vector3(x / _other.x, y / _other.y, z / _other.z); }
        
        double norm() const { return norm_cash; }
        void normalize();

        Vector3 vector_poduct(const Vector3 _other) const ;
        double scalar_poduct(const Vector3 _other) const ;

        void show();
};

#endif
