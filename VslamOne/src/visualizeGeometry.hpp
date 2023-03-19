#pragma once
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iomanip>

struct RotationMatrix
{
  Eigen::Matrix3d matrix = Eigen::Matrix3d::Identity();
};
struct TranslationVector
{
  Eigen::Vector3d trans = Eigen::Vector3d::Zero();
};
struct DrawQuaternion {
  Eigen::Quaterniond q;
};

using namespace std;
using namespace Eigen;

ostream &operator<<(ostream &out, const RotationMatrix &r) {
  out.setf(ios::fixed);
  Matrix3d matrix = r.matrix;
  out << '=';
  out << "[" << setprecision(2) << matrix(0, 0) << "," << matrix(0, 1) << ","
      << matrix(0, 2) << "],"
      << "[" << matrix(1, 0) << "," << matrix(1, 1) << "," << matrix(1, 2)
      << "],"
      << "[" << matrix(2, 0) << "," << matrix(2, 1) << "," << matrix(2, 2)
      << "]";
  return out;
}

istream &operator>>(istream &in, RotationMatrix &r) { return in; }

ostream &operator<<(ostream &out, const TranslationVector &t) {
  out << "=[" << t.trans(0) << ',' << t.trans(1) << ',' << t.trans(2) << "]";
  return out;
}

istream &operator>>(istream &in, TranslationVector &t) { return in; }

ostream &operator<<(ostream &out, const DrawQuaternion quat) {
  auto c = quat.q.coeffs();
  out << "=[" << c[0] << "," << c[1] << "," << c[2] << "," << c[3] << "]";
  return out;
}

istream &operator>>(istream &in, const DrawQuaternion quat) { return in; }
