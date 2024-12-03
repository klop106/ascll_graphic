#ifndef OBJECT
#define OBJECT

#include "poligon.h"

#include <fstream>
#include <vector>
#include <json/json.h>

struct Material
{
    float spec_reflect = 0;
    float diffuse_reflect = 0;
    float specular_exponent = 0;
    float specularity = 0;
    float attenuation[3] = {0, 0, 0};

    Material(
        float _spec_reflect,
        float _diffuse_reflect,
        float _specular_exponent,
        float _specularity,
        float _attenuation[3]
    ) :
        spec_reflect(_spec_reflect),
        diffuse_reflect(_diffuse_reflect),
        specular_exponent(_specular_exponent),
        specularity(_specularity)
    {
        for (size_t i = 0; i < 3; i++)
        {
            attenuation[i] = _attenuation[i];
        } 
    }
    Material() :
        spec_reflect(0),
        diffuse_reflect(0),
        specular_exponent(0),
        specularity(0)
    {
        for (size_t i = 0; i < 3; i++)
        {
            attenuation[i] = 0;
        } 
    }
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

    Object transform(const LinearTransformation _transform);
};

#endif