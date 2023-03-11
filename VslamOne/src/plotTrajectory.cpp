#include "drawTrajectory.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <pangolin/pangolin.h>
#include <unistd.h>

// Path to the trajectory file
std::string trajectoryFile = "";

int main(int argc, char **argv) {
  std::vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d>>
      poses;
  std::ifstream fin(trajectoryFile);
  if (!fin) {
    std::cout << "Cannot find trajectory file at " << trajectoryFile
              << std::endl;
    return 1;
  }
  while (!fin.eof()) {
    double time, tx, ty, tz, qx, qy, qz, qw;
    fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
    Eigen::Isometry3d Twr(Eigen::Quaterniond(qx, qy, qz, qw));
    Twr.pretranslate(Eigen::Vector3d(tx, ty, tz));
    poses.push_back(Twr);
  }
  std::cout << "Read total" << poses.size() << "pose entries" << std::endl;
  // Draw trajectories in pangolin
  DrawTrajectory(poses);
  return 0;
}
