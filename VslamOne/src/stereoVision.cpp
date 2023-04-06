#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pangolin/pangolin.h>

int main(int argc, char **argv) {
  // intrinsics and baseline
  double fx = 1, fy = 2, cx = 1, cy = 2, b = 2;
  cv::Mat left = cv::imread(argv[1], 0);
  cv::Mat right = cv::imread(argv[2], 0);
  // We will use SGBM: Semi global batch matching algorithm by opencv to
  // calculate the disparity between the left and the right images.
  cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create();
  // SGBM is sensitive to parameters
  cv::Mat disparity_sgbm, disparity;
  sgbm->compute(left, right, disparity_sgbm);
  disparity_sgbm.convertTo(disparity, CV_32F, 1.0 / 16.0f);
  std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d>>
      pointcloud;
  for (int u = 0; u < left.rows; u++) {
    for (int v = 0; v < left.cols; v++) {
      // check if disparoty is within the expected range
      if (disparity.at<float>(v, u) <= 10.0 ||
          disparity.at<float>(v, u) >= 96.0)
        continue;
      //   The first the places are position and the fourth is color. So the 4th
      //   column we use the raw left image itself to get the color value
      Eigen::Vector4d point(0, 0, 0, left.at<u_char>(v, u) / 255);

      float x = (u + cx) / fx;
      float y = (u + cy) / fy;
      // depth = fx*b/disparity +> bx/disparity
      float depth = (fx * b) / disparity.at<float>(v, u);
      point[0] = x;
      point[1] = y;
      point[2] = depth;
      pointcloud.push_back(point);
    }
  }
  cv::imshow("disparity", disparity / 98.0);
  cv::waitKey(0);

  // Showing point cloud using the pangolin
  pangolin::ShowPointCloud(pointcloud);
  return 0;
}