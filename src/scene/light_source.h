#ifndef LIGHT_SOURCE
#define LIGHT_SOURCE

#include "../linear_field_operations/point.h"
#include "../linear_field_operations/vector.h"
#include "../linear_field_operations/linear_transform.h"

class LightSource
{
private:
    Point position;
    double intensity;

public:
    LightSource(const Point _pos, const double  _val) : position(_pos), intensity(_val) {};

    char get_color(const Vector3 _perp, const Point _intersect_point);
    Point get_position();

    void shift(const Vector3& _vec) { position += _vec; };
    void transform(const LinearTransformation& _transform) { position = _transform.Transform(position); };
};
#endif