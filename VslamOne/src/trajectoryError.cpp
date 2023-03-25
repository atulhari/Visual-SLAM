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
typedef std::vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>>
    trajectoryType;
trajectoryType readTrajectory(std::string &path);
// main
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

// readTrajectory
trajectoryType readTrajectory(const std::string &path) {
  std::ifstream fin(path);
  trajectoryType trajectory;
  if (!fin) {
    std::cerr << "File not found at" << path << std::endl;
    return trajectory;
  }
  while (!fin.eof()) {
    double time, tx, ty, tz, qx, qy, qz, w;
    fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> w;
    Sophus::SE3d path(Eigen::Quaterniond(qx, qy, qz, w),
                      Eigen::Vector3d(tx, ty, tz));
    trajectory.push_back(path);
  }
  return trajectory;
}