#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>   // opencv
#include <Eigen/Dense>

using namespace std;

int main(int argc, char const *argv[])
{
    // cv::namedWindow("RRT", cv::WINDOW_NORMAL);

    cv::Mat img = cv::imread("RDR.jpeg");

    cv::imshow("Red Dead", img);
    cv::waitKey();
    cout << "CMakeLists.txt 编译测试" << endl;
    cv::destroyAllWindows();
    return 0;
}
