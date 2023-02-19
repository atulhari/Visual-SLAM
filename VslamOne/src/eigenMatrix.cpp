#include <ctime>
#include <iostream>

/// Example program for Eigen library

// Eigen Core
#include <Eigen/Core>
// Dense matric operations
#include <Eigen/Dense>

#define MATRIX_SIZE 50

int main(int argc, char **argv) {
  // Eigen Matrix definition
  Eigen::Matrix<float, 2, 3> matrix23;
  // Eigen Vector Definition
  Eigen::Vector3d vec3d;
  // vec3d is same as matrix13
  Eigen::Matrix<float, 3, 1> matrix13;
  // Mat3d is matrix33
  Eigen::Matrix3d mat3d = Eigen::Matrix3d::Zero();
  // Dynamic size representation of matrix
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrixDynamic;
  // Simpler Dynamic representation
  Eigen::MatrixXd matrixXd;
  // Input data intialization
  matrix23 << 1, 2, 3, 4, 5, 6;
  std::cout << "matrix 2x3 from 1 to 6: \n" << matrix23 << std::endl;

  // Access elements in the matrix
  std::cout << "print matrix 2x3:" << std::endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++)
      std::cout << matrix23(i, j) << "\t";
    std::cout << std::endl;
  }

  vec3d << 3, 2, 1;
  matrix13 << 4, 5, 6;
  // Different type of matrix should be static casted
  Eigen::Matrix<double, 2, 1> resultMat = matrix23.cast<double>() * vec3d;
  std::cout << "[1,2,3;4,5,6]*[3,2,1]=" << resultMat.transpose() << std::endl;

  // Matrix operations

  // Random matrix
  mat3d = Eigen::Matrix3d::Random();
  std::cout << "Random matrix: \n" << mat3d << std::endl;
  std::cout << "Transpose: \n" << mat3d.transpose() << std::endl;
  std::cout << "Sum: " << mat3d.sum() << std::endl;
  std::cout << "Trace: " << mat3d.trace() << std::endl;
  std::cout << "times 10: \n" << 10 * mat3d << std::endl;
  std::cout << "Inverse: \n" << mat3d.inverse() << std::endl;
  std::cout << "Det: \n" << mat3d.determinant() << std::endl;

  // Eigenvalues
  // Real symmetric matrix can guarantee successful diagonalization
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigenSolver(mat3d.transpose() *
                                                             mat3d);
  std::cout << "Eigen values:" << eigenSolver.eigenvalues() << std::endl;
  std::cout << "Eigen vectors:" << eigenSolver.eigenvectors() << std::endl;

  // Solving equations MatrixNN * x = vecNd (Ax = b)
  // Inversion is the most direct approach, but the time for inversion operation
  // is large

  Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrixNN =
      Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
  matrixNN = matrixNN * matrixNN.transpose();
  Eigen::Matrix<double, MATRIX_SIZE, 1> vecNd =
      Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

  clock_t timeSett = clock(); // timing
  Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrixNN.transpose() * vecNd;
  std::cout << "Time for normal inverse is:"
            << 1000 * (clock() - timeSett) / (double)CLOCKS_PER_SEC << "ms"
            << std::endl;
  std::cout << "x = " << x.transpose() << std::endl;

  // Usually solved by marix decomposition, such as QR decomposition, the speed
  // will be much faster.
  timeSett = clock();
  x = matrixNN.colPivHouseholderQr().solve(vecNd);
  std::cout << "The time for QR decomposition is: "
            << 1000 * (clock() - timeSett) / (double)CLOCKS_PER_SEC << "ms"
            << std::endl;
  std::cout << "x = " << x.transpose() << std::endl;

  // For positve definite matrix you could also use a cholesky decomposition to
  // solve equations

  timeSett = clock();
  x = matrixNN.ldlt().solve(vecNd);
  std::cout << "The time for ldlt decomposition (cholesky) is: "
            << 1000 * (clock() - timeSett) / (double)CLOCKS_PER_SEC << "ms"
            << std::endl;
  std::cout << "x = " << x.transpose() << std::endl;
  return 0;
}