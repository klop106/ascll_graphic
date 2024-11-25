#ifndef LINEAR_OPERATIONS
#define LINEAR_OPERATIONS

#include <cstddef>
#include "point.h"
#include "vector.h"

class LinearTransformation
{
private:
   double coeffs[3][3];

public:
    LinearTransformation(const double _matr[3][3]);

    Point Transform(const Point _vec) const;    
    Vector3 Transform(const Vector3 _vec) const;    
};

#endif