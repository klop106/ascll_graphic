#include "vector_2d.h"

Vector2::Vector2(const double _u, const double _v)
{
    u = _u;
    v = _v;
    calc_norm();
}

Point Vector2::generate_3d_point(const Vector3 _ort_x, const Vector3 _ort_y, const Point _ref_point)
{
    return _ref_point + _ort_x * u + _ort_y * v;
}