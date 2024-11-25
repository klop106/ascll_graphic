#include "point_of_view.h"

PointOfView::PointOfView(const Vector3 _normal, const Vector3 _tangen_x, const Vector3 _tangen_y, const Point _pos)
{
    position = _pos;

    if ((_tangen_x.scalar_poduct(_tangen_y) != 0) && (_tangen_x.scalar_poduct(_normal) != 0))
    {
        std::cerr << "not orts";
        exit(1);
    }

    view_direction = _normal;
    x_orientation = _tangen_x; 
    y_orientation =_tangen_y;
}
    
void PointOfView::shift(const Vector3& _vec) { position = position + _vec; }

void PointOfView::transform(const LinearTransformation& _transform)
{
    view_direction = _transform.Transform(view_direction);
    x_orientation = _transform.Transform(x_orientation);
    y_orientation = _transform.Transform(y_orientation);

    position = _transform.Transform(position);
}

void PointOfView::show()
{
    
    std::cout << position.x << std::endl;
    std::cout << position.y << std::endl;
    std::cout << position.z << std::endl;
    std::cout << std::endl;

}