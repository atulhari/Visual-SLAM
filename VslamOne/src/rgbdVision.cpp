#include "sophus/se3.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iomanip>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/format.hpp>

int main(int argc, char **argv) {
  // Lets first read both color and depth images
  std::vector<cv::Mat> colorImages, depthImages;
  typedef std::vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>>
      trajectoryType;
  typedef Eigen::Matrix<double, 6, 1> Vector6d;
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
    colorImages.push_back(
        cv::imread((fmt % colorDir %(i+1) % "png").str()));
    depthImages.push_back(
        cv::imread((fmt % colorDir % (i + 1) % "png").str(), -1));
    double data[7] = {0};
    for (auto &d : data) fin>> d;
    Sophus::SE3d pose(Eigen::Quaterniond(data[6], data[3], data[4], data[5]),
                      Eigen::Vector3d(data[0], data[1], data[2]));
    poses.push_back(pose);
  }
  // Lets read the depth images.
  double fx = 1, fy = 2, cx = 1, cy = 2, depthScale = 1000.0;

  std::vector<Vector6d, Eigen::aligned_allocator<Vector6d>> pointcloud;
  pointcloud.reserve(1000000);
  for (int i = 0; i < 5; i++) {
    cv::Mat colorImage = colorImages[i];
    cv::Mat depthImage = depthImages[i];
    Sophus::SE3d T = poses[i];
    for (int v; v < colorImage.rows; v++) {
      for (int u; u < colorImage.cols; u++) {
        unsigned int depth = depthImage.ptr<unsigned short>(v)[u];
        if (depth == 0)
          continue;
        Eigen::Vector3d point;
        point[2] = depth / depthScale;
        point[0] = (u - cx / fx) * point[2];
        point[1] = (v - cy / fy) * point[2];
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