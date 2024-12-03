#ifndef RENDER
#define RENDER

#include "../linear_field_operations/point.h"
#include "../linear_field_operations/vector.h"

#include "../scene/point_of_view.h"
#include "../scene/object.h"
#include "../scene/light_source.h"

#include "frame.h"

#include <vector>
#include <cmath>

typedef std::tuple<bool, Point, Poligon*, Material> info;

class Render
{
private:
    Frame* projection_plane;

    PointOfView* camera;
    std::vector<Object>* objects;
    std::vector<LightSource>* light_sources;

public:
    Render(PointOfView* const _pov,std::vector<Object>* const _objects, std::vector<LightSource>* const _lights, Frame* const _pic) 
    : camera(_pov), objects(_objects), light_sources(_lights), projection_plane(_pic) {};

    void render();
    void show_camera_pos();
    float cast_ray(const Poligon* _polig, const Point& _intersect_point, const Material& _material, const size_t resurse_rate = 1) const;

    Vector3 reflect(const Vector3& _normal, const Point& _intersect_point, const Point& _light_position) const;
    info intersect(const Vector3& _direc, const Point& _pos, const Poligon* _parent_polig) const;
    Point get_pixel_position(const size_t _i, const size_t _j);

};

#endif