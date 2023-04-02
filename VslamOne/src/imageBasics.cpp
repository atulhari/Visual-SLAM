#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define LOG(x) std::cout<< x << std::endl;

int main(int argc, char **argv)
{
    // read the image from argv 
    cv::Mat image;
    image = cv::imread(argv[1]);

    // check if the data exist 
    if(image.data == nullptr)
    {
        std::cerr <<"The file path"<<argv[1]<<"is empty";
        return 0;
    }
    // Print the basic information of the image  
    LOG("Number of cols:");
    LOG(image.cols);
    cv::imshow("image",image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}