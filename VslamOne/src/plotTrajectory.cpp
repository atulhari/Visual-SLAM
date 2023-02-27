// #include "drawTrajectory.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <pangolin/pangolin.h>
#include <unistd.h>

// Path to the trajectory file
std::string trajectoryFile = "";

void DrawTrajectory(std::vector<Eigen::Isometry3d,
                                Eigen::aligned_allocator<Eigen::Isometry3d>>);

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
    double time, tx, ty, tz, qx, qy, qz, qz, qw;
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

void DrawTrajectory(
    std::vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d>>
        poses) {
  // Create pangolin window and plot the trajectory
  pangolin::CreateWindowAndBind("Trajectory Viewver", 1024, 768);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  pangolin::OpenGlRenderState sCam(
      pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
      pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0));
  pangolin::View &dCam = pangolin::CreateDisplay()
                             .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
                             .SetHandler(new pangolin::Handler3D(sCam));
  while (pangolin::ShouldQuit() == false) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dCam.Activate(sCam);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2);
    for (size_t i = 0; i < poses.size(); i++) {
      // Draw  three axes of each pose
      Eigen::Vector3d Ow = poses[i].translation();
      Eigen::Vector3d Xw = poses[i] * (0.1 * Eigen::Vector3d(1, 0, 0));
      Eigen::Vector3d Yw = poses[i] * (0.1 * Eigen::Vector3d(0, 1, 0));
      Eigen::Vector3d Zw = poses[i] * (0.1 * Eigen::Vector3d(0, 0, 1));
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Xw[0], Xw[1], Xw[2]);
      glColor3f(0.0, 1.0, 0.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Yw[0], Yw[1], Yw[2]);
      glColor3f(0.0, 0.0, 1.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Zw[0], Zw[1], Zw[2]);
      glEnd();
    }
    // Draw a connection
    for (size_t i = 0; i < poses.size() - 1; i++) {
      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      auto p1 = poses[i], p2 = poses[i + 1];
      glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
      glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
      glEnd();
    }
    pangolin::FInishFrame();
    usleep(5000);
    // sleep 5ms
  }
}