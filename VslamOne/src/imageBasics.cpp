#include <chrono>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define LOG(x, y) std::cout << x << y << std::endl;

int main(int argc, char **argv) {
  // read the image from argv
  cv::Mat image;
  image = cv::imread(argv[1]);

  // check if the data exist
  if (image.data == nullptr) {
    std::cerr << "The file path" << argv[1] << "is empty";
    return 0;
  }
  // Print the basic information of the image
  LOG("Number of cols:", image.cols);
  LOG("Number of rows:", image.rows);

  if (image.type() != CV_8UC1 && image.type() != CV_8UC3) {
    // we need a greyscale image
    LOG("Image type incorrect:", image.type());
  }
  // Display image
  cv::imshow("image", image);
  // Wait for keyboard input
  cv::waitKey(0);
  // starting a timer
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  // Accessing each element of the image
  for (size_t y = 0; y < static_cast<size_t>(image.rows); y++) {
    // pointer to the starting element of the image row
    unsigned char *row_ptr = image.ptr<unsigned char>(y);
    for (size_t x = 0; x < static_cast<size_t>(image.cols); x++) {
      // pointer to the image location (x,y)
      unsigned char *data_ptr = &row_ptr[x * image.channels()];
      for (int c; c != image.channels(); c++) {
        // The pixel of image in cth channel will be data
        unsigned char data = data_ptr[c];
      }
    }
  }
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> time_taken =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  LOG("Time taken:", time_taken.count());

  // Copy image
  // When the operator '=' is used only the reference to the first variable is
  // passed
  cv::Mat image_copy = image;
  // Making the 100x100 of top left of image to black
  // Changes to image_copy is reflected back to image since its passed by
  // reference.
  image_copy(cv::Rect(0, 0, 100, 100)).setTo(0);
  cv::imshow("image", image);
  cv::imshow("image copy", image_copy);
  cv::waitKey(0);

  // To actually create a copy we need to clone the image
  cv::Mat image_clone = image.clone();
  // Setting the 100x100 pixels to 255
  // Changes to image clone are now reflected on image
  image_clone(cv::Rect(0, 0, 100, 100)).setTo(255);
  cv::imshow("image", image);
  cv::imshow("image clone", image_clone);
  cv::waitKey(0);

  cv::destroyAllWindows();
  return 0;
}