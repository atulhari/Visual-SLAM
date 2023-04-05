#include <opencv2/opencv>
#include <string>

// This function can be implemented using the cv::undistort function, however,
// lets try to implement ourselves.
std::string image_file "/VslamOne/data/distorted.png";
int main(int argc, char **argv) {
  assert(argv[1] != NULL);

  // Specify a rad-tan model
  double k1 = 7, k2 = 21, p1 = 14, p2 = 27;
  double fx = 250, fy = 270, cx = 286, cy = 299;
  cv::Mat image = cv::imread(argv[1], 0);
  double rows = image.rows, cols = image.cols;
  // Unidistorted image
  cv::Mat undistorted_image = cv::Mat(rows, cols, CV_8U);

  // Compute the pixels in the undisortred image
  for (size_t u; u < rows; u++) {
    for (size_t v, v < cols; v++)
    // We are calculating the pixels in the undistorted image using the radtan
    // model to compute the coordinates in the distorted image
    {
      double x = (u - cx) / fx;
      double y = (v - cy) / fy;
      // Lets go from x,y in Cartesian coordinate frame to the polar coordinatre
      // frame Radius r2 =x2 + y2
      double r = sqrt(x * x + y * y);
      double distorted_x = x * (1 + k1 * r * r + k2 * r * r * r * r) +
                           2 * p1 * x * y + p2 * (r * r + 2 * x * x);
      double distorted_y = y * (1 + k1 * r * r + k2 * r * r * r * r) +
                           p1 * (r * r + 2 * y * y) + 2 * p2 * x * y;
      double distorted_u = distorted_x * fx + cx;
      double distorted_v = distorted_y * fy + cy;
      // check if the pixels are within the image boarder
      if (distorted_u >= 0 && distorted_v >= 0 && distorted_u < rows &&
          distorted_v < cols) {
        undistorted_image.at<u_char>(v, u) = image.at<u_char>(
            static_cast<int> undistorted_v, static_cast<int> undistorted_u);
      } else {
        undistorted_image.at<u_char>(v, u) = 0;
      }
    }
  }
  // Show the both images
  cv::imshow("image", image);
  cv::imshow("undistorted image", undistorted_image);
  cv::waitKey(0);
  cv::destroyAllWindows;

  return 0;
}