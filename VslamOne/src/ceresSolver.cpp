#include <ceres/ceres.h>
#include <chrono>
#include <iostream>
#include <opencv2/core/core.hpp>

struct CURVE_FITTING_COST {
  // Given a data this functor calcluates the error and rertutn it as the
  // residual value.
  CURVE_FITTING_COST(double x, double y) : _x(x), _y(y) {}
  template<typename T>
  bool operator()(const T *const abc, T *residual) const {
    // y - exp(ax^2 + bx + c)
    residual[0] =
        T(_y) - ceres::exp(abc[0] * T(_x) * T(_x) + abc[1] * T(_x) + abc[2]);
    return true;
  }
  const double _x, _y; // x,y is the data
};

int main(int argc, char **argv) {
  // Ground truth values
  double ar = 1.0, br = 2.0, cr = 1.0;

  // Initial estimate
  double ae = 2.0, be = -1.0, ce = 5.0;
  int N = 100;

  double wSigma = 1.0;
  double invSigma = 1.0 / wSigma;

  cv::RNG rng;

  // Create data
  std::vector<double> xData, yData;
  for (int i = 0; i < N; i++) {
    double x = static_cast<double>(i) / 100;
    xData.push_back(x);
    yData.push_back(exp(ar * x * x + br * x + cr) +
                    rng.gaussian(wSigma * wSigma));
  }

  double abc[3] = {ae, be, ce};

  ceres::Problem problem;
  for (int i = 0; i < N; i++) {
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(
            new CURVE_FITTING_COST(xData[i], yData[i])),
        nullptr, abc);
  }
  ceres::Solver::Options options;
  options.linear_solver_type = ceres::DENSE_NORMAL_CHOLESKY;
  options.minimizer_progress_to_stdout = true;
  ceres::Solver::Summary summary;

  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  ceres::Solve(options, &problem, &summary);
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> timeUsed =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Solve time:" << timeUsed.count() << "seconds" << std::endl;
  std::cout << summary.BriefReport() << std::endl;
  std::cout << "Estimated a,b,c =";
  for (auto a : abc) {
    std::cout << a << "";
  }
  std::cout << std::endl;
  return 0;
}