#include <pangolin/pangolin.h>
#include <Eigen/Core>
#include <Eigen/Geometry>


using namespace Eigen;

struct RotationMatrix
{
   Matrix3d matrix = Matrix3d::Identity();
};
struct TranslationVector
{
    Vector3d vector = vector3d::Zero();
};
struct DrawQuaternion
{
    Quaterniond q;
};
