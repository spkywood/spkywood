#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/ximgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

/**
 * @brief 直线检测
 * 
 * 先在输入图像上，应用canny边缘检测；然后根据在canny边缘图像上进行分析，找到直线。
 */

int main(int argc, char const *argv[])
{
    std::string in;
    cv::CommandLineParser parser(argc, argv, "{@input|corridor.jpg|input image}{help h||show help message}");
    
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    in = cv::samples::findFile(parser.get<std::string>("@input"));

    cv::Mat image = cv::imread(in, cv::IMREAD_GRAYSCALE);

    if( image.empty() )
    {
        return -1;
    }

    // Create FLD detector
    // Param               Default value   Description
    // length_threshold    10            - Segments shorter than this will be discarded
    // distance_threshold  1.41421356    - A point placed from a hypothesis line
    //                                     segment farther than this will be
    //                                     regarded as an outlier
    // canny_th1           50            - First threshold for
    //                                     hysteresis procedure in Canny()
    // canny_th2           50            - Second threshold for
    //                                     hysteresis procedure in Canny()
    // canny_aperture_size 3            - Aperturesize for the sobel operator in Canny().
    //                                     If zero, Canny() is not applied and the input
    //                                     image is taken as an edge image.
    // do_merge            false         - If true, incremental merging of segments
    //                                     will be performed
    int length_threshold = 10;
    float distance_threshold = 1.41421356f;
    double canny_th1 = 50.0;
    double canny_th2 = 50.0;
    int canny_aperture_size = 3;
    bool do_merge = false;

    // cv::Ptr<cv::ximgproc::FastLineDetector> cv::ximgproc::createFastLineDetector(	
    //     int 	_length_threshold = 10,                 // 小于此数的将被丢弃
    //     float 	_distance_threshold = 1.414213562f, // 距离假设线段远于此的点将被视为离群。
    //     double 	_canny_th1 = 50.0,                  // Canny()中的第一个阈值
    //     double 	_canny_th2 = 50.0,                  // Canny()中的第二个阈值
    //     int 	_canny_aperture_size = 3,               // Canny()中的sobel算子大小。如果为零，则不应用Canny()，输入图像被视为边缘图像。
    //     bool 	_do_merge = false                   // 如果为真，将进行片段的增量合并
    // )    
    // Creates a smart pointer to a FastLineDetector object and initializes it.
    // Parameters
    //     _length_threshold	10 - Segment shorter than this will be discarded
    //     _distance_threshold	1.41421356 - A point placed from a hypothesis line segment farther than this will be regarded as an outlier
    //     _canny_th1	50 - First threshold for hysteresis procedure in Canny()
    //     _canny_th2	50 - Second threshold for hysteresis procedure in Canny()
    //     _canny_aperture_size	3 - Aperturesize for the sobel operator in Canny(). If zero, Canny() is not applied and the input image is taken as an edge image.
    //     _do_merge	false - If true, incremental merging of segments will be performed

    cv::Ptr<cv::ximgproc::FastLineDetector> fld = 
        cv::ximgproc::createFastLineDetector(
            length_threshold,
            distance_threshold, 
            canny_th1, 
            canny_th2, 
            canny_aperture_size,
            do_merge);

    // typedef Vec<float, 4> cv::Vec4f
    // #include <opencv2/core/matx.hpp>
    std::vector<cv::Vec4f> lines;

    // Because of some CPU's power strategy, it seems that the first running of
    // an algorithm takes much longer. So here we run the algorithm 10 times
    // to see the algorithm's processing time with sufficiently warmed-up
    // CPU performance.
    for (int run_count = 0; run_count < 5; run_count++) {
        double freq = cv::getTickFrequency();
        lines.clear();
        int64 start = cv::getTickCount();
        // Detect the lines with FLD
        fld->detect(image, lines);
        double duration_ms = double(cv::getTickCount() - start) * 1000 / freq;
        std::cout << "Elapsed time for FLD " << duration_ms << " ms." << std::endl;
    }
    
    // Show found lines with FLD
    cv::Mat line_image_fld(image);
    fld->drawSegments(line_image_fld, lines);
    cv::imshow("FLD result", line_image_fld);
    cv::waitKey(1);

    cv::Ptr<cv::ximgproc::EdgeDrawing> ed = cv::ximgproc::createEdgeDrawing();
    ed->params.EdgeDetectionOperator = cv::ximgproc::EdgeDrawing::SOBEL;
    ed->params.GradientThresholdValue = 38;
    ed->params.AnchorThresholdValue = 8;
    std::vector<cv::Vec6d> ellipses;
    
    for (int run_count = 0; run_count < 5; run_count++) {
        double freq = cv::getTickFrequency();
        lines.clear();
        int64 start = cv::getTickCount();
        // Detect edges
        //you should call this before detectLines() and detectEllipses()
        ed->detectEdges(image);
        // Detect lines
        ed->detectLines(lines);
        double duration_ms = double(cv::getTickCount() - start) * 1000 / freq;
        std::cout << "Elapsed time for EdgeDrawing detectLines " << duration_ms << " ms." << std::endl;
        start = cv::getTickCount();
        // Detect circles and ellipses
        ed->detectEllipses(ellipses);
        duration_ms = double(cv::getTickCount() - start) * 1000 / freq;
        std::cout << "Elapsed time for EdgeDrawing detectEllipses " << duration_ms << " ms." << std::endl;
    }

    cv::Mat edge_image_ed = cv::Mat::zeros(image.size(), CV_8UC3);
    
    std::vector< std::vector<cv::Point> > segments = ed->getSegments();
    
    for (size_t i = 0; i < segments.size(); i++)
    {
        const cv::Point* pts = &segments[i][0];
        int n = (int)segments[i].size();
        polylines(edge_image_ed, &pts, &n, 1, false, cv::Scalar((rand() & 255), (rand() & 255), (rand() & 255)), 1);
    }
    
    cv::imshow("EdgeDrawing detected edges", edge_image_ed);
    
    
    cv::Mat line_image_ed(image);
    fld->drawSegments(line_image_ed, lines);

    // 画圆和椭圆
    // Draw circles and ellipses
    for (size_t i = 0; i < ellipses.size(); i++)
    {
        cv::Point center((int)ellipses[i][0], (int)ellipses[i][1]);
        cv::Size axes((int)ellipses[i][2] + (int)ellipses[i][3], (int)ellipses[i][2] + (int)ellipses[i][4]);
        double angle(ellipses[i][5]);
        cv::Scalar color = ellipses[i][2] == 0 ? cv::Scalar(255, 255, 0) : cv::Scalar(0, 255, 0);
        ellipse(line_image_ed, center, axes, angle, 0, 360, color, 2, cv::LINE_AA);
    }

    cv::imshow("EdgeDrawing result", line_image_ed);
    cv::waitKey();
    return 0;
}
