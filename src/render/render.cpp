#include "render.h"

void Render::render()
{
    projection_plane->clean_up();
    for (size_t x = 0; x < projection_plane->get_size_x(); x++)
    {
        for (size_t y = 0; y < projection_plane->get_size_y(); y++)
        {
            Vector3 direction = get_pixel_position(x, y) - camera->get_position();
            IntersectionInfo intersect_info = intersect(direction, camera->get_position(), nullptr);
            if (intersect_info.get_intersected())
            {
                Vector3 ray_direction = light_sources->get_position() - intersect_info.get_intersection_point();
                if (!intersect(ray_direction, intersect_info.get_intersection_point(), intersect_info.get_intersected_poligon()).get_intersected())
                {
                    char color = light_sources->get_color(
                        intersect_info.get_intersected_poligon()->get_normal(), 
                        intersect_info.get_intersection_point()
                    );
                    projection_plane->mark_pixel(x, y, color);
                }
            }
        }
    }
}

Point Render::get_pixel_position(const size_t _i, const size_t _j)
{
    return projection_plane->get_pixel_position(_i, _j).generate_3d_point(
        camera->get_x_orientation(), 
        camera->get_y_orientation(), 
        camera->get_position() + camera->get_view_direction());
}

IntersectionInfo Render::intersect(const Vector3 _direc, const Point _pos, const Poligon* _parent_polig)
{
    double min_distance = __DBL_MAX__;
    IntersectionInfo info;
    for (auto it = objects->begin(); it != objects->end(); it++) {
        IntersectionInfo intersect = (*it).intersect(_direc, _pos, _parent_polig);
        if (intersect.get_intersected()) { 
            Point point = intersect.get_intersection_point();
            double distance = (point - _pos).norm();
            if (min_distance > distance) 
            { 
                min_distance = distance; 
                info = IntersectionInfo(true, point, intersect.get_intersected_poligon());
            }
        }
    } 
    return info;  
}

void Render::show_cmera_pos()
{
    camera->show();
}