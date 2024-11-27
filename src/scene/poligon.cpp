#include "poligon.h"

//--------------------Poligon methods--------------------

Poligon::Poligon(const Point _points[3])
{
    for(int id = 0; id < 3; id++){ nodes[id] = _points[id]; }    
    calc_minors();
}

Poligon::Poligon(const Point _point1, const Point _point2, const Point _point3)
{
    nodes[0] = _point1;
    nodes[1] = _point2;
    nodes[2] = _point3;
    calc_minors();
}

void Poligon::shift(const Vector3 _vec)
{
    for (size_t i = 0; i < 3; i++) { nodes[i] += _vec; }
    calc_minors();
}

void Poligon::transform(const LinearTransformation _transform) 
{ 
    for (size_t i = 0; i < 3; i++) { nodes[i] = _transform.Transform(nodes[i]); }
    calc_minors();
}

std::tuple<bool, Point, Poligon*> Poligon::intersect(const Vector3 _direc, const Point _pos)
{
    if (abs(_direc.x * minors[0] - _direc.y * minors[1] + _direc.z * minors[2]) < 0.001)
    {
       return std::tuple<bool, Point, Poligon*>{false,  Point(), this};
    }

    Point intersect_coord = intersect_point(_direc, _pos);
    if ((intersect_coord - _pos).scalar_poduct(_direc) < 0)
    {
       return std::tuple<bool, Point, Poligon*>{false,  Point(), this};
    }
    
    double A1 = calc_trinagle_square(intersect_coord, nodes[0], nodes[1]);
    double A2 = calc_trinagle_square(intersect_coord, nodes[0], nodes[2]);
    double A3 = calc_trinagle_square(intersect_coord, nodes[1], nodes[2]);
    double A = calc_trinagle_square(nodes[0], nodes[1], nodes[2]);

    if (abs(A1 + A2 + A3 - A) > 0.001)
    {
       return std::tuple<bool, Point, Poligon*>{false,  Point(), this};
    }
    return std::tuple<bool, Point, Poligon*>{true,  intersect_coord, this};
}

Point Poligon::intersect_point(const Vector3 _direc, const Point _pos)
{
    Point intersect_coord;
    double t;

    Vector3 diff = _pos - nodes[0];
    t = (- diff.x * minors[0] + diff.y * minors[1] - diff.z * minors[2]) / (_direc.x * minors[0] - _direc.y * minors[1] + _direc.z * minors[2]);

    intersect_coord.x = _direc.x * t + _pos.x;
    intersect_coord.y = _direc.y * t + _pos.y;
    intersect_coord.z = _direc.z * t + _pos.z;

    return intersect_coord;
}

void Poligon::calc_minors()
{
    minors[0] = (nodes[1].y - nodes[0].y) * (nodes[2].z - nodes[0].z) - (nodes[2].y - nodes[0].y) * (nodes[1].z - nodes[0].z);
    minors[1] = (nodes[1].x - nodes[0].x) * (nodes[2].z - nodes[0].z) - (nodes[2].x - nodes[0].x) * (nodes[1].z - nodes[0].z);
    minors[2] = (nodes[1].x - nodes[0].x) * (nodes[2].y - nodes[0].y) - (nodes[2].x - nodes[0].x) * (nodes[1].y - nodes[0].y);    
}

double Poligon::calc_trinagle_square(const Point _point1, const Point _point2, const Point _point3)
{
    double a = (_point1 - _point2).norm();
    double b = (_point1 - _point3).norm();
    double c = (_point3 - _point2).norm();

    double p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

void Poligon::show()
{
    for (size_t i = 0; i < 3; i++)
    {
        std::cout << nodes[i].x << std::endl;
        std::cout << nodes[i].y << std::endl;
        std::cout << nodes[i].z << std::endl;
        std::cout << std::endl;
    }
}
