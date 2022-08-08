#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

int main()
{
    //Mat img = imread("plane.png");
    Mat img = imread("t11.jpg");

    namedWindow("Input Image", cv::WINDOW_KEEPRATIO);
    namedWindow("G", cv::WINDOW_KEEPRATIO);

    //gray scale conversion from colour image
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);

    //compute sobel in X direction
    Mat img_blur, img_canny, img_edges;

    //canny edge detector
    blur( img_gray, img_blur, Size(3,3) );
    Canny( img_blur, img_edges, 100, 180, 3 );

    vector<Vec4i> lines; // will hold the results of the detection
    HoughLinesP(img_edges, lines, 1, CV_PI/180, 180, 4, 13 ); // runs the actual detection

    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines.at(i);
        line(img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, LINE_AA);
    }

    //output image
    
    
    imshow("Input Image", img);
    imshow("G", img_edges);
    //imshow("G", img_edges);

    waitKey(0);



    return 0;
}