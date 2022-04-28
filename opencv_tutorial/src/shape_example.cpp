#include <opencv2/shape.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

static void help()
{
    printf("\n"
            "This program demonstrates a method for shape comparison based on Shape Context\n"
            "You should run the program providing a number between 1 and 20 for selecting an image in the folder ../data/shape_sample.\n"
            "Call\n"
            "./shape_example [number between 1 and 20, 1 default]\n\n");
}

static vector<Point> simpleContour( const Mat& currentQuery, int n=300 )
{
    vector<vector<Point> > _contoursQuery;
    vector <Point> contoursQuery;
    findContours(currentQuery, _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
    for (size_t border=0; border<_contoursQuery.size(); border++)
    {
        for (size_t p=0; p<_contoursQuery[border].size(); p++)
        {
            contoursQuery.push_back( _contoursQuery[border][p] );
        }
    }
    // In case actual number of points is less than n
    int dummy=0;
    for (int add=(int)contoursQuery.size()-1; add<n; add++)
    {
        contoursQuery.push_back(contoursQuery[dummy++]); //adding dummy values
    }
    // Uniformly sampling
    cv::randShuffle(contoursQuery);
    vector<Point> cont;
    for (int i=0; i<n; i++)
    {
        cont.push_back(contoursQuery[i]);
    }
    return cont;
}

int main(int argc, char** argv)
{
    string path = "data/shape_sample/";
    cv::CommandLineParser parser(argc, argv, "{help h||}{@input|1|}");

    if (parser.has("help"))
    {
        help();
        return 0;
    }

    int indexQuery = parser.get<int>("@input");
    if (!parser.check())
    {
        parser.printErrors();
        help();
        return 1;
    }
    if (indexQuery < 1 || indexQuery > 20)
    {
        help();
        return 1;
    }

    cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();
    Size sz2Sh(300,300);
    stringstream queryName;
    queryName << path << indexQuery << ".jpeg";
    std::cout << queryName.str() << std::endl;
    
    cv::Mat query = cv::imread(queryName.str(), cv::IMREAD_GRAYSCALE);
    cv::Mat queryToShow;
    
    resize(query, queryToShow, sz2Sh, 0, 0, cv::INTER_LINEAR_EXACT);
    imshow("QUERY", queryToShow);
    
    moveWindow("TEST", 0,0);
    vector<Point> contQuery = simpleContour(query);
    int bestMatch = 0;
    float bestDis=FLT_MAX;
    
    for ( int ii = 1; ii <= 1; ii++ )
    {
        if ( ii == indexQuery ) continue;
        waitKey(30);
        stringstream iiname;
        iiname << path << ii <<".jpeg";
        cout << "name: " << iiname.str() << endl;
        cv::Mat iiIm = cv::imread(iiname.str(), 0);
        cv::Mat iiToShow;
        cv::resize(iiIm, iiToShow, sz2Sh, 0, 0, INTER_LINEAR_EXACT);
        cv::imshow("TEST", iiToShow);
        cv::moveWindow("TEST", sz2Sh.width+50, 0);
        vector<Point> contii = simpleContour(iiIm);
        float dis = mysc->computeDistance( contQuery, contii );
        if ( dis< bestDis )
        {
            bestMatch = ii;
            bestDis = dis;
        }
        std::cout<<" distance between "<<queryName.str()<<" and "<<iiname.str()<<" is: "<<dis<<std::endl;
    }

    destroyWindow("TEST");
    
    stringstream bestname;
    bestname << path << bestMatch <<".jpeg";
    Mat iiIm=imread(bestname.str(), 0);
    Mat bestToShow;
    resize(iiIm, bestToShow, sz2Sh, 0, 0, INTER_LINEAR_EXACT);
    imshow("BEST MATCH", bestToShow);
    moveWindow("BEST MATCH", sz2Sh.width+50,0);
    waitKey();
    return 0;
}