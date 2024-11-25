#ifndef RENDER
#define RENDER

#include "../linear_field_operations/point.h"
#include "../linear_field_operations/vector.h"

#include "../scene/point_of_view.h"
#include "../scene/object.h"
#include "../scene/light_source.h"

#include "frame.h"

#include <vector>

class Render
{
private:
    Frame* projection_plane;

    PointOfView* camera;
    std::vector<Object>* objects;
    LightSource* light_sources;

public:
    Render(PointOfView* const _pov,std::vector<Object>* const _objects, LightSource* const _lights, Frame* const _pic) 
    : camera(_pov), objects(_objects), light_sources(_lights), projection_plane(_pic) {};

    void render();

    IntersectionInfo intersect(const Vector3 _direc, const Point _pos, const Poligon* _parent_polig);

    Point get_pixel_position(const size_t _i, const size_t _j);

    void show_cmera_pos();
};

#endif