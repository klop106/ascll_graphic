#ifndef OBJECT
#define OBJECT

#include "poligon.h"

#include <fstream>
#include <vector>
#include <json/json.h>

struct Material
{
    float spec_reflect = 1;
    float diffuse_reflect = 2;
    float specular_exponent = 0;

    Material(float _ind, float _albedo, float _spec) : spec_reflect(_ind), diffuse_reflect(_albedo), specular_exponent(_spec) {};
    Material() : spec_reflect(0), diffuse_reflect(0), specular_exponent(0) {};
};


typedef std::tuple<bool, Point, Poligon*, Material> info;
typedef std::tuple<bool, Point, Poligon*> inter_info;


class Object
{
friend class Render;

private:
    std::vector<Poligon> poligons;
   
    double* get_points(const std::string _str);
    int* get_node_ids(const std::string _str);
    Material material;
    
public:
    Object(std::string _file_name, const Material& _material);

    info intersect(const Vector3 _direc, const Point _pos, const Poligon* _parent_polig);

    Object shift(const Vector3 _vec);
    Object transform(const LinearTransformation _transform);
};

#endif