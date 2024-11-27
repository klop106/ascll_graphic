#include "linear_transform.h"

LinearTransformation::LinearTransformation(const double _matrix[3][3])
{
    for (size_t i = 0; i < 3; i++) { for (size_t j = 0; j < 3; j++) { coeffs[i][j] = _matrix[i][j]; } }
}

LinearTransformation::LinearTransformation()
{
    for (size_t i = 0; i < 3; i++) { for (size_t j = 0; j < 3; j++) { coeffs[i][j] = 0; } }
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

LinearTransformation LinearTransformation::scaleTransform(const double _scale)
{
    for (size_t i = 0; i < 3; i++) { for (size_t j = 0; j < 3; j++) { coeffs[i][j] = _scale ? i == j : 0; } }
    return *this;
}

LinearTransformation LinearTransformation::rotationTransform(const Vector3& _axis, const double _phi)
{
    Vector3 norm = _axis / _axis.norm();
    coeffs[0][0] = cos(_phi) + (1 - cos(_phi)) * norm.x * norm.x;
    coeffs[0][1] = (1 - cos(_phi)) * norm.x * norm.y - sin(_phi) * norm.z;
    coeffs[0][2] = (1 - cos(_phi)) * norm.x * norm.z + sin(_phi) * norm.y;
    coeffs[1][0] = (1 - cos(_phi)) * norm.x * norm.y + sin(_phi) * norm.z;
    coeffs[1][1] = cos(_phi) + (1 - cos(_phi)) * norm.y * norm.y;
    coeffs[1][2] = (1 - cos(_phi)) * norm.z * norm.y - sin(_phi) * norm.x;
    coeffs[2][0] = (1 - cos(_phi)) * norm.x * norm.z - sin(_phi) * norm.y;
    coeffs[2][1] = (1 - cos(_phi)) * norm.z * norm.y + sin(_phi) * norm.x;
    coeffs[2][2] = cos(_phi) + (1 - cos(_phi)) * norm.z * norm.z;
    return *this;
}
