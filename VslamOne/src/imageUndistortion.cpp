#include <opencv2/opencv>
#include <string>

string image_file "";
int main(int argc, char **argv)
{       
    assert(argv[1]!=NULL);

    // Specify a rad-tan model 
    double k1 = 7, p1=14, p2=27;
    double fx=250, fy=270, cx=286, cy=299;
    cv::Mat image = cv::imread(argv[1],0);
    double rows = image.rows, cols = image.cols;
    cv::Mat undistorted_image = cv::Mat(rows,cols,CV_8U);

    return 0;

}