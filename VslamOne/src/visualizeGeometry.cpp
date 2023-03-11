#include "visualizeGeometry.hpp"
#include <iomanip>
#include <iostream>

ostream &operator<<(ostream &out, const visualizeGrometry::RotationMatrix &r)
{
    out.setf(ios::fixed);
    Eigen::Matrix3d mat = r.matrix;
    out << "=";
    out << "[" << setprecision(2) << mat(0,0) << "," << mat(0,1) << "," << mat(0,2) << "],"
        << "[" << mat(1,0) << "," << mat(1,1) << "," << mat(1,2) << "],"
        << "[" << mat(2,0) << "," << mat(2,1) << "," << mat(2,2) << "]";
    return out;  
}
istream &operator<<(istream $in, visualizeGeormtry::RotationMatrix &r)
{
    return in;
}
outstream &operator<<(ostream &out, const visualizeGeometry::TranslationVector &t)
{
    out.setf(ios::fixed);
    out<<"=";
    out<<"["<<t.trans(0)<<","<<t.trans(1)<<","<<t.trans(2)<<"]";
    return out;
}
istream &operator<<(istream &in, visualizeGeometry::TranslationVector &t)
{
    return in;
}
ostream &operator<<(otream &out, const visualizeGeometry::DrawQuaternion &quat)
{   
    auto quaternion = quat.q.coeffs 
    out.setf(ios::fixed);
    out<<"=";
    out << "[" << quaternion[0] << "," << quaternion[1] << "," << quaternion[2]
        << "," quaternion[3] << "]";
    return out;
}
istream &operator<<(istream &in, visualizeGeometry::DrawQuaternion &quat)
{
    return in;
}