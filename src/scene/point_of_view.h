#ifndef POV
#define POV

#include "../linear_field_operations/point.h"
#include "../linear_field_operations/vector.h"
#include "../linear_field_operations/linear_transform.h"

class PointOfView
{
private:
    Vector3 view_direction;
    Vector3 x_orientation;
    Vector3 y_orientation;

    Point position;

public:
    PointOfView(const Vector3 _normal, const Vector3 _tangen_x, const Vector3 _tangen_y, const Point _pos); 

    void transform(const LinearTransformation& _transform);

    Vector3 get_x_orientation() const { return x_orientation; }
    Vector3 get_y_orientation() const { return y_orientation; }
    Vector3 get_view_direction() const { return view_direction; }
    Point get_position() const { return position; }

    void show();
};

#endif