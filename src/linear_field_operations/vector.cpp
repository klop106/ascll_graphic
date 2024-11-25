#include "vector.h"

void Vector3::normalize() 
{ 
    x = x / norm_cash; 
    y = y / norm_cash; 
    z = z / norm_cash; 
}

Vector3 Vector3::vector_poduct(const Vector3 _other) const 
{ 
    return Vector3(
            y * _other.z - z * _other.y, 
            - x * _other.z + z * _other.x, 
            x * _other.y - y * _other.x
        ); 
}

double Vector3::scalar_poduct(const Vector3 _other) const 
{ 
    return (x * _other.x + y * _other.y + z * _other.z); 
}

Vector3 Vector3::operator=(const Vector3 _other)
{
    x = _other.x;
    y = _other.y;
    z = _other.z;
    calc_norm();
    return *this;
}

void Vector3::show()
{
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << z << std::endl;
}
