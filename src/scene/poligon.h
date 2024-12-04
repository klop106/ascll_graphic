#ifndef POLIGON
#define POLIGON

#include "../linear_field_operations/point.h"
#include "../linear_field_operations/vector.h"
#include "../linear_field_operations/linear_transform.h"

#include <tuple>

class Poligon
{
private:
    double minors[3];
    Point nodes[3];

    void calc_minors(); 
    double calc_trinagle_square(const Point _point1, const Point _point2, const Point _point3);

    Point intersect_point(const Vector3 _direc, const Point _pos);

public:
    Poligon(const Point _points[3]);
    Poligon(const Point _point1, const Point _point2, const Point _point3);
    
    void transform(const LinearTransformation _transform);

    std::tuple<bool, Point, Poligon*> intersect(const Vector3 _direc, const Point _pos);

    Vector3 get_normal() const {return Vector3(minors[0], -minors[1], minors[2]).normalize(); };

    void show();
};

#endif