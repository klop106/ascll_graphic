#ifndef LINEAR_OPERATIONS
#define LINEAR_OPERATIONS

#include <cstddef>
#include <cmath>

#include "point.h"
#include "vector.h"

class LinearTransformation
{
private:
   double coeffs[4][4];

   void init(); 

public:
    LinearTransformation(const double _matr[4][4]);
    LinearTransformation();

    LinearTransformation scaleTransform(const double _scale);
    LinearTransformation rotationTransform(const Vector3& _axis, const double _phi);
    LinearTransformation shiftTransform(const Vector3& _shift);
   
    Point Transform(const Point _vec) const;    
    Vector3 Transform(const Vector3 _vec) const;    
};

#endif