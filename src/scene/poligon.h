#ifndef POLIGON
#define POLIGON

#include "../linear_field_operations/point.h"
#include "../linear_field_operations/vector.h"
#include "../linear_field_operations/linear_transform.h"


class Poligon;

struct IntersectionInfo
{
private:
    bool intersected;
    Point intersection_point;
    Poligon* intersected_poligon;

public:
    IntersectionInfo(const bool _intersect, const Point _inter_point, Poligon* _inter_polig);
    IntersectionInfo(): intersected(false), intersection_point(Point()), intersected_poligon(nullptr) {};

    IntersectionInfo operator=(const IntersectionInfo& _info);

    bool get_intersected() { return intersected; }
    Point get_intersection_point() { return intersection_point; }
    Poligon* get_intersected_poligon() { return intersected_poligon; }
};


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
    
    void shift(const Vector3 _vec);
    void transform(const LinearTransformation _transform);

    IntersectionInfo intersect(const Vector3 _direc, const Point _pos);

    Vector3 get_normal() {return Vector3(-minors[0], minors[1], -minors[2]); };

    void show();
};

#endif