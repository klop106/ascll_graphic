#include "render.h"

void Render::render()
{
    const char GRADIENT[10] = ".:;+=xX$&";
    const int GRADIENT_LENGTH = 8;
    for (size_t pixel_x = 0; pixel_x < projection_plane->get_size_x(); pixel_x++)
    {
        for (size_t pixel_y = 0; pixel_y < projection_plane->get_size_y(); pixel_y++)
        {
            Vector3 direction = get_pixel_position(pixel_x, pixel_y) - camera->get_position();
            info intersect_info = intersect(direction, camera->get_position(), nullptr);
            if (std::get<0>(intersect_info))
            {
                float color = cast_ray(
                    std::get<2>(intersect_info), 
                    std::get<1>(intersect_info),
                    std::get<3>(intersect_info)
                );
                projection_plane->mark_pixel(
                    pixel_x, 
                    pixel_y, 
                    GRADIENT[static_cast<size_t>(std::min(color * GRADIENT_LENGTH, static_cast<float>(GRADIENT_LENGTH)))]
                );
            }
        }
    }
}


float Render::cast_ray(const Poligon* _polig, const Point& _intersect_point, const Material& _material, const size_t resurse_rate) const
{
    double luminous_value = 0;
    Vector3 perp = _polig->get_normal();
    for (auto it = light_sources->begin(); it != light_sources->end(); it++) {
        Vector3 direction  = ((*it).get_position() - _intersect_point).normalize();
        double distance = ((*it).get_position() - _intersect_point).norm();
        double attenuation_const  = 1 / (_material.attenuation[0] + _material.attenuation[1] * distance + _material.attenuation[2] * distance * distance);
        if (!std::get<0>(intersect(direction, _intersect_point, _polig)))
        {
            Vector3 on_pov_direction = (camera->get_position() - _intersect_point).normalize();
            luminous_value += attenuation_const * std::max(
                0., perp.scalar_poduct(direction)
            ) * (*it).get_intensity() * _material.diffuse_reflect * (1 - _material.specularity);
            luminous_value += attenuation_const * std::max(
                0., pow(on_pov_direction.scalar_poduct(reflect(perp, _intersect_point, (*it).get_position())), _material.specular_exponent)
            ) * (*it).get_intensity() * _material.spec_reflect * (1 - _material.specularity);
        }
        if (resurse_rate < 4)
        {
            info reflect_info = intersect(
                reflect(perp, _intersect_point, camera->get_position()),
                _intersect_point,
                _polig
            );
            if (std::get<0>(reflect_info))
            {
                luminous_value += cast_ray(
                    std::get<2>(reflect_info), 
                    std::get<1>(reflect_info),
                    std::get<3>(reflect_info),
                    resurse_rate + 1
                ) * _material.specularity * attenuation_const;
            }  
        }
    }
    return luminous_value;
}




Vector3 Render::reflect(const Vector3& _normal, const Point& _intersect_point, const Point& _light_position) const
{
    Vector3 incidance_direction = (_intersect_point - _light_position).normalize();
    Vector3 normal_component = _normal * incidance_direction.scalar_poduct(_normal);
    return (incidance_direction - normal_component * 2).normalize();
}


Point Render::get_pixel_position(const size_t _i, const size_t _j)
{
    return projection_plane->get_pixel_position(_i, _j).generate_3d_point(
        camera->get_x_orientation(), 
        camera->get_y_orientation(), 
        camera->get_position() + camera->get_view_direction());
}


info Render::intersect(const Vector3& _direc, const Point& _pos, const Poligon* _parent_polig) const
{
    double min_distance = __DBL_MAX__;
    info _info = std::make_tuple(false, Point(), nullptr, Material());
    for (auto it = objects->begin(); it != objects->end(); it++) {
        info intersect = (*it).intersect(_direc, _pos, _parent_polig);
        if (std::get<0>(intersect)) { 
            Point point = std::get<1>(intersect);
            double distance = (point - _pos).norm();
            if (min_distance > distance) 
            { 
                min_distance = distance; 
                _info = intersect;
            }
        }
    } 
    return _info;  
}

void Render::show_camera_pos()
{
    camera->show();
}