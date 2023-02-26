#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <iostream>

// The program will demostrate the use of Eigen geometry modeule.

int main(int argc, char **argv) {
  Eigen::Matrix3d rotMat = Eigen::Matrix3d::Identity();

  // Rotate vector 45 degree along z axis
  Eigen::AngleAxisd rotVec(M_PI / 4, Eigen::Vector3d(0, 0, 1));

  std::cout.precision(3);
  // converting rotation vector to matrix inline
  std::cout << "Rotation matrix = \n" << rotVec.matrix() << std::endl;

  // This conversion can also be assigned directly
  rotMat = rotVec.toRotationMatrix();

  // Coordinate transformatrion with AngleAxis
  Eigen::Vector3d v(1, 0, 0);
  Eigen::Vector3d vRotated = rotVec * v;

  std::cout << "(1,0,0) after rotation using angle axis = "
            << vRotated.transpose() << std::endl;

  // This can be done straight froward using a roation matrix
  vRotated = rotMat * v;
  std::cout << "(1,0,0) after rotation using Rotation matrix = "
            << vRotated.transpose() << std::endl;

  // The rotation matrix can be directly converted to Euler angles
  Eigen::Vector3d eulerAngles = rotMat.eulerAngles(2, 1, 0);
  // The order used above is z,y,x which is roll, pitch, yaw order The z
  // forward, y right and x up.

  std::cout << "The yaw, pitch, roll = " << eulerAngles.transpose()
            << std::endl;

  // Euclidean transformation matrix using Eignen::Isometry
  Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
  // Even though it says isometry3d the matrix is 4x4

  // Rotate T according to the rotation vector
  T.rotate(rotVec);

  // Set the translation vector to (1,3,4)
  T.pretranslate(Eigen::Vector3d(1, 3, 4));
  std::cout << "Transformation matrix = \n" << T.matrix() << std::endl;

  // Use the transformation matrix T to do coordinate transform
  Eigen::Vector3d vTransformed = T * v;
  // This is equivalent to R*v +t
  std::cout << "v transformed = \n" << vTransformed.transpose() << std::endl;

  // For affine and projective transformations, use Eigen::Affine3d and
  // Eigen::Projective3d

  // Quaternion
  // Assign AngleAxis directly to quaternion and vice versa
  Eigen::Quaterniond q = Eigen::Quaterniond(rotVec);
  std::cout << "Quaternion from rotation vector = \n"
            << q.coeffs().transpose() << std::endl;
  // The order of the quaternion is (x,y,z,w)

  // A rotation matrix can also be assigned to the quaternion
  q = Eigen::Quaterniond(rotMat);
  std::cout << "Quaternion from rotation matrix = \n"
            << q.coeffs().transpose() << std::endl;

  // Rotating a vector with quaternion and use overloaded multiplication
  // This is equivalent to v' = qvq{-1} mathematically
  vRotated = q * v;
  std::cout << "(1,0,0) after rotation = \n"
            << vRotated.transpose() << std::endl;

  // When expressed as a regular vector multplication this can be represented as
  // below
  std::cout
      << "Mathematically= \n"
      << (q * Eigen::Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose()
      << std::endl;

  return 0;
}