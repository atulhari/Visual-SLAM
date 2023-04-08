#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pangolin/pangolin.h>
#include <unistd.h>

void ShowPointcloud(
    const std::vector<Eigen::Vector4d,
                      Eigen::aligned_allocator<Eigen::Vector4d>> &pointcloud);

int main(int argc, char **argv) {
  // intrinsics and baseline
  double fx = 718.856, fy = 718.856, cx = 607.1928, cy = 185.2157, b = 0.573;
  cv::Mat left = cv::imread(argv[1], 0);
  cv::Mat right = cv::imread(argv[2], 0);
  // We will use SGBM: Semi global batch matching algorithm by opencv to
  // calculate the disparity between the left and the right images.
  cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(
      0, 96, 9, 8 * 9 * 9, 32 * 9 * 9, 1, 63, 10, 100, 32);
  // SGBM is sensitive to parameters
  cv::Mat disparity_sgbm, disparity;
  sgbm->compute(left, right, disparity_sgbm);
  disparity_sgbm.convertTo(disparity, CV_32F, 1.0 / 16.0f);
  std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d>>
      pointcloud;
  for (int v = 0; v < left.rows; v++) {
    for (int u = 0;u  < left.cols; u++) {
      // check if disparoty is within the expected range
      if (disparity.at<float>(v, u) <= 0.0 ||
          disparity.at<float>(v, u) >= 96.0)
        continue;
      //   The first the places are position and the fourth is color. So the 4th
      //   column we use the raw left image itself to get the color value
      Eigen::Vector4d point(0, 0, 0, left.at<u_char>(v, u) / 255);

      float x = (u - cx) / fx;
      float y = (v - cy) / fy;
      // depth = fx*b/disparity +> bx/disparity
      float depth = (fx * b) / disparity.at<float>(v, u);
      point[0] = x * depth;
      point[1] = y * depth;
      point[2] = depth;
      pointcloud.push_back(point);
    }
  }
  cv::imshow("disparity", disparity / 98.0);
  cv::waitKey(0);

  // Showing point cloud using the pangolin
  ShowPointcloud(pointcloud);
  return 0;
}

void ShowPointcloud(
    const std::vector<Eigen::Vector4d,
                      Eigen::aligned_allocator<Eigen::Vector4d>> &pointcloud) {

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
      glColor3f(p[3], p[3], p[3]);
      glVertex3d(p[0], p[1], p[2]);
    }
    glEnd();
    pangolin::FinishFrame();
    usleep(5000); // sleep 5 ms
  }
  return;
}