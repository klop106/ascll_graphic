#include "linear_transform.h"

LinearTransformation::LinearTransformation(const double _matrix[3][3])
{
    for (size_t i = 0; i < 3; i++) { for (size_t j = 0; j < 3; j++) { coeffs[i][j] = _matrix[i][j]; } }
}

Point LinearTransformation::Transform(const Point _vec) const
{
    Point result_vec;
    
    result_vec.x = coeffs[0][0] * _vec.x + coeffs[0][1] * _vec.y + coeffs[0][2] * _vec.z;
    result_vec.y = coeffs[1][0] * _vec.x + coeffs[1][1] * _vec.y + coeffs[1][2] * _vec.z;
    result_vec.z = coeffs[2][0] * _vec.x + coeffs[2][1] * _vec.y + coeffs[2][2] * _vec.z;
    
    return result_vec;
}

Vector3 LinearTransformation::Transform(const Vector3 _vec) const
{
    Vector3 result_vec;
    
    result_vec.x = coeffs[0][0] * _vec.x + coeffs[0][1] * _vec.y + coeffs[0][2] * _vec.z;
    result_vec.y = coeffs[1][0] * _vec.x + coeffs[1][1] * _vec.y + coeffs[1][2] * _vec.z;
    result_vec.z = coeffs[2][0] * _vec.x + coeffs[2][1] * _vec.y + coeffs[2][2] * _vec.z;
    
    return result_vec;
}
