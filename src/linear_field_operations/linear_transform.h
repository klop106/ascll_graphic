#ifndef LINEAR_OPERATIONS
#define LINEAR_OPERATIONS

#include <cstddef>
#include <cmath>

#include "point.h"
#include "vector.h"

class LinearTransformation
{
private:
   double coeffs[3][3];

public:
    LinearTransformation(const double _matr[3][3]);
    LinearTransformation();

    LinearTransformation scaleTransform(const double _scale);
    LinearTransformation rotationTransform(const Vector3& _axis, const double _phi);
   
    Point Transform(const Point _vec) const;    
    Vector3 Transform(const Vector3 _vec) const;    
};

#endif