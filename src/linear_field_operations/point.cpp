#include "point.h"

Point Point::operator=(const Point _point)
{
    x = _point.x;
    y = _point.y;
    z = _point.z;
    return *this;
}

void Point::show()
{
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << z << std::endl;
}