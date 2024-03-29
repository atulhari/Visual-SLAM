#include <Eigen/Core>
#include <chrono>
#include <cmath>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/base_vertex.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/g2o_core_api.h>
#include <g2o/core/optimization_algorithm_dogleg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <iostream>
#include <opencv2/core/core.hpp>

// Unary problem only one vertex and many edges that points to the same vertex

// Vertex is a 3d vector
class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  // Override the reset function , which is a pure virtual function
  void setToOriginImpl() override { _estimate << 0, 0, 0; }

  void oplusImpl(const double *update) override {
    _estimate += Eigen::Vector3d(update);
  }

  // the dummy read and write functionsl
  bool read(std::istream &in) {}
  bool write(std::ostream &out) const {}
};

// Edgeis a 1D error term, connected to exactly one vertex
class CurveFittingEdge
    : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex> {
public:
  double _x;
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  CurveFittingEdge(double x) : BaseUnaryEdge(), _x(x){};

  // define the error term computation
  void computeError() override {
    const CurveFittingVertex *v =
        static_cast<const CurveFittingVertex *>(_vertices[0]);
    const Eigen::Vector3d abc = v->estimate();
    _error[0] =
        _measurement - std::exp(abc[0] * _x * _x + abc[1] * _x + abc[2]);
  }

  // jacobian
  void linearizeOplus() override {
    const CurveFittingVertex *v =
        static_cast<const CurveFittingVertex *>(_vertices[0]);
    const Eigen::Vector3d abc = v->estimate();
    double y = std::exp(abc[0] * _x * _x + abc[1] * _x + abc[0] * _x);
    _jacobianOplusXi[0] = -_x * _x * y;
    _jacobianOplusXi[1] = -_x * y;
    _jacobianOplusXi[2] = -y;
  }

  bool read(std::istream &in) {}
  bool write(std::ostream &out) const {}
};

int main(int argc, char **argv) {
  // Ground truth values
  double ar = 1.0, br = 2.0, cr = 1.0;

  // Initial estimate
  double ae = 2.0, be = -1.0, ce = 5.0;
  int N = 100;

  double wSigma = 1.0;

  cv::RNG rng;

  // Create data
  std::vector<double> xData, yData;
  for (int i = 0; i < N; i++) {
    double x = static_cast<double>(i) / 100;
    xData.push_back(x);
    yData.push_back(exp(ar * x * x + br * x + cr) +
                    rng.gaussian(wSigma * wSigma));
  }

  // create a solver object
  typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;
  typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType>
      LinearSolverType;

  auto solver = new g2o::OptimizationAlgorithmGaussNewton(
      std::make_unique<BlockSolverType>(std::make_unique<LinearSolverType>()));

  // Create a optimiser object
  g2o::SparseOptimizer optimiser;

  optimiser.setAlgorithm(solver);
  optimiser.setVerbose(true);

  // lets add the vertex
  CurveFittingVertex *v = new CurveFittingVertex();
  v->setEstimate(Eigen::Vector3d(ae, be, ce));
  v->setId(0);
  optimiser.addVertex(v);

  // Lets add the edge
  // There are multiple edges and we will loop through the data to add them.
  for (int i = 0; i < N; i++) {
    CurveFittingEdge *edge = new CurveFittingEdge(xData[i]);
    edge->setId(i);
    edge->setVertex(0, v);
    edge->setMeasurement(yData[i]);
    Eigen::Matrix<double, 1, 1> info =
        Eigen::Matrix<double, 1, 1>::Identity() * 1 / (wSigma * wSigma);
    edge->setInformation(info);
    optimiser.addEdge(edge);
  }

  // Start the optimisation
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  optimiser.initializeOptimization();
  optimiser.optimize(10);
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> timeUsed =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  // Print results
  Eigen::Vector3d abcEstimate = v->estimate();
  std::cout << "Estimated model: " << abcEstimate.transpose() << std::endl;
  return 0;
}
