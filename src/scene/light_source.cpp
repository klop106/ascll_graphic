#include "light_source.h"

char LightSource::get_color(const Vector3 _perp, const Point _intersect_point) 
{
    const char GRADIENT[10] = ".:;+=xX$&";
    const int GRADIENT_LENGTH = 8;
    Vector3 direction  = position - _intersect_point;
    direction.normalize();
    return GRADIENT[static_cast<size_t>((_perp.scalar_poduct(direction) / _perp.norm() + 1) / 2 * GRADIENT_LENGTH)];
}

Point LightSource::get_position()
{
    return position;
}