#include "sophus/se3.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <boost/format.hpp>
#include <iomanip>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pangolin/pangolin.h>
#include <unistd.h>

typedef std::vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>>
    trajectoryType;
typedef Eigen::Matrix<double, 6, 1> Vector6d;

void ShowPointcloud(
    const std::vector<Vector6d, Eigen::aligned_allocator<Vector6d>>
        &pointcloud);

int main(int argc, char **argv) {
  // Lets first read both color and depth images
  std::vector<cv::Mat> colorImages, depthImages;
  trajectoryType poses;
  std::ifstream fin(argv[3]);
  std::string colorDir(argv[1]);
  std::string depthDir(argv[2]);
  if (!fin) {
    std::cerr << "The pose file is empty" << std::endl;
    return 1;
  }
  for (int i = 0; i < 5; i++) {
    boost::format fmt("%s/%d.%s");
    colorImages.push_back(cv::imread((fmt % colorDir % (i + 1) % "png").str()));
    depthImages.push_back(
        cv::imread((fmt % depthDir % (i + 1) % "pgm").str(), -1));
    double data[7] = {0};
    for (auto &d : data)
      fin >> d;
    Sophus::SE3d pose(Eigen::Quaterniond(data[6], data[3], data[4], data[5]),
                      Eigen::Vector3d(data[0], data[1], data[2]));
    poses.push_back(pose);
  }

  double cx = 325.5;
  double cy = 253.5;
  double fx = 518.0;
  double fy = 519.0;
  double depthScale = 1000.0;

  std::vector<Vector6d, Eigen::aligned_allocator<Vector6d>> pointcloud;
  pointcloud.reserve(1000000);
  for (int i = 0; i < 5; i++) {
    cv::Mat colorImage = colorImages[i];
    cv::Mat depthImage = depthImages[i];
    Sophus::SE3d T = poses[i];
    for (int v = 0; v < colorImage.rows; v++) {
      for (int u = 0; u < colorImage.cols; u++) {
        unsigned int depth = depthImage.ptr<unsigned short>(v)[u];
        if (depth == 0)
          continue;
        Eigen::Vector3d point;
        point[2] = depth / depthScale;
        point[0] = (u - cx) * point[2] / fx;
        point[1] = (v - cy) * point[2] / fy;
        Eigen::Vector3d worldPoint = T * point;
        Vector6d p;
        p.head<3>() = worldPoint;
        p[5] = colorImage.data[v * colorImage.step + u * colorImage.channels()];
        // blue
        p[4] = colorImage.data[v * colorImage.step + u * colorImage.channels() + 1];
        // green
        p[3] = colorImage.data[v * colorImage.step + u * colorImage.channels() + 2];
        // red
        pointcloud.push_back(p);
      }
    }
  }
  std::cout << "Pointcloud has " << pointcloud.size() << " number of points."
            << std::endl;
  ShowPointcloud(pointcloud);
  return 0;
}

void ShowPointcloud(
    const std::vector<Vector6d, Eigen::aligned_allocator<Vector6d>>
        &pointcloud) {

  if (pointcloud.empty()) {
    std::cerr << "Point cloud is empty!" << std::endl;
    return;
  }

  pangolin::CreateWindowAndBind("Point Cloud Viewer", 1024, 768);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  pangolin::OpenGlRenderState s_cam(
      pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
      pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0));

  pangolin::View &d_cam = pangolin::CreateDisplay()
                              .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175),
                                         1.0, -1024.0f / 768.0f)
                              .SetHandler(new pangolin::Handler3D(s_cam));

  while (pangolin::ShouldQuit() == false) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    d_cam.Activate(s_cam);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glPointSize(2);
    glBegin(GL_POINTS);
    for (auto &p : pointcloud) {
      glColor3f(p[3] / 255.0, p[4] / 255.0, p[5] / 255.0);
      glVertex3d(p[0], p[1], p[2]);
    }
    glEnd();
    pangolin::FinishFrame();
    usleep(5000); // sleep 5 ms
  }
  return;
}