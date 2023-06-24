#include <Eigen/Core>
#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
  // Ground truth values
  double ar = 1.0, br = 2.0, cr = 1.0;

  // Initial estimate
  double ae = 2.0, be = -1.0, ce = 5.0;

  // Number of data points
  int N = 100;

  // Noise parameters
  double w_sigma = 1.0;
  double inv_sigma = 1 / w_sigma;
  cv::RNG rng;

  // Data
  // y = exp (ax2 + bx+c) + w
  std::vector<double> x_data, y_data;

  for (int i = 0; i < N; i++)
  {
    double x = i / N; 
    x_data.push_back(x);
      double y =
          exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma * w_sigma);
      y_data.push_back(y);
  }

  // Gauss Newton
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  int iterations = 100;
  double cost = 0, lastCost = 0;

  for (int iter = 0; iter < iterations; iter++) {
    // Hessian Matrix H * dx = g
    Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
    // bias
    Eigen::Vector3d g = Eigen::Vector3d::Zero();
    cost = 0;

    for (int i = 0; i < N; i++) {
      double x = x_data[i], y = y_data[i];
      double error = y - exp(ae * x * x + be * x + ce);
      Eigen::Vector3d J;
      J[0] = -x * x * exp(ae * x * x + be * x + ce);
      J[1] = -x * exp(ae * x * x + be * x + ce);
      J[2] = -exp(ae * x * x + be * x + ce);
      H += inv_sigma * inv_sigma * J * J.transpose();
      g += -inv_sigma * inv_sigma * error * J;
      cost += error * error;
    }

    // solve for H.dx = g
    Eigen::Vector3d dx = H.ldlt().solve(g);
    if (isnan(dx[0])) 
    {
      std::cerr << "Result is nan!" << std::endl;
      break;
    }

    if (iter > 0 && cost >= lastCost) {
      std::cout<< "Cost" << cost << ">= Last cost" << lastCost << std::endl;
      break;
    }

    ae += dx[0];
    be += dx[1];
    ce += dx[2];
    lastCost = cost;

    std::cout << "Total cost:" << cost << ",\t\tupdate:" << dx.transpose()
              << ",\t\testimated params:" << ae << be << ce << std::endl;
  }
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> time_used =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Total time used:" << time_used.count() << "seconds"
            << std::endl;
  std::cout << "estimated abc = " << ae << ", " << be << ", " << ce
            << std::endl;
  return 0;
}