#include "drawTrajectory.hpp"
#include "sophus/se3.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <fstream>
#include <iostream>
#include <pangolin/pangolin.h>
#include <unistd.h>

std::string groundTruthFile = "/path/to/gt";
std::string estimatedTrajectoryFile = "/path/to/extimate";

int main(int argc, char **argv) {
  trajectoryType gtTrajectory = readTrajectory(groundTruthFile);
  trajectoryType estimatedTrajectory = readTrajectory(estimatedTrajectoryFile);
  assert(!gtTrajectory.empty() && !estimatedTrajectory.empty());
  assert(gtTrajectory.size() == estimatedTrajectory.size());
  // calculate error
  double rmse = 0;
  for (size_t i = 0; i < gtTrajectory.size(); i++)
  {
    Sophus::SE3d p1(gtTrajectory[i]);
    Sophus::SE3d p2(estimatedTrajectory[i]);
    double error = (p1.inverse() * p2).log().norm();
    rmse += error * error;
  }
  rmse = rmse / double(gtTrajectory.size());
  rmse = sqrt(rmse);
  std::cout << "The rmse error is:" << rmse << std::endl;
  DrawTrajectory(gtTrajectory);
  DrawTrajectory(estimatedTrajectory);
  return 0;
}
