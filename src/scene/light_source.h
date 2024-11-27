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

    Point get_position();
    double get_intensity();

    void shift(const Vector3& _vec) { position += _vec; };
    void transform(const LinearTransformation& _transform) { position = _transform.Transform(position); };
};
#endif