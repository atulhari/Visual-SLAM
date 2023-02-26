#include <Eigen/Core>
#include <Eigen/Geometry>
#include <algorithm>
#include <iostream>
#include <vector>

// This program is used to demonstrate transforming a point p1 represented in the
// coordinate system of 1 to 2.
int main(int argc, char **argv) {
  // Declaring the quaternions
  Eigen::Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);

  // Normalizing the quaternions
  q1.normalize();
  q2.normalize();

  // Declaring the translation vectors and the point to be transformed
  Eigen::Vector3d t1(0.3,0.1,0.1), t2(-0.1,0.5,0.3);
  Eigen::Vector3d p1(0.5,0,0.2);
  
  // Declaring the transformation matrix with quaternion
  Eigen::Isometry3d T1w(q1), T2w(q2);
  // Applying the translation 
  T1w.pretranslate(t1);
  T2w.pretranslate(t2);

  // Applying the coordinate transformation
  Eigen::Vector3d p2 = T2w * T1w.inverse() * p1;
  std::cout<<std::endl<<p2.transpose()<<std::endl;
  return 0;
}