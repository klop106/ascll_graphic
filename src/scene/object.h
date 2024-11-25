#ifndef OBJECT
#define OBJECT

#include "poligon.h"

#include <fstream>
#include <vector>
#include <json/json.h>

class Object
{
friend class Render;

private:
    std::vector<Poligon> poligons;
   
    double* get_points(const std::string _str);
    int* get_node_ids(const std::string _str);
    
public:
    Object(std::string _file_name);

    IntersectionInfo intersect(const Vector3 _direc, const Point _pos, const Poligon* _parent_polig);

    void shift(const Vector3 _vec);
    void transform(const LinearTransformation _transform);
};

#endif