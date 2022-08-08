#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
    namedWindow("input", WINDOW_KEEPRATIO);

    Mat img = imread("test2.jpg");
    Mat grayimg = img.clone();
    cv::cvtColor(img, grayimg, COLOR_BGR2GRAY);

    vector<Vec3f> circles;
    HoughCircles(grayimg, circles, HOUGH_GRADIENT, 1, 100, 100, 50, 30, 80);

    for(int i=0; i<circles.size(); i++)
    {
        stringstream str;
        str << "Id: " << i;

        Point pt(circles.at(i)[0], circles.at(i)[1]);
        circle(img, pt, circles.at(i)[2], Scalar(0,0,255), 3, LINE_AA);
        circle(img, pt, 2, Scalar(0,0,0), 3, LINE_AA);

        putText(img, str.str(), pt, FONT_HERSHEY_DUPLEX, 1, Scalar(0,0,0), 2);
    }

    for(size_t i=0; i<circles.size(); i++) {
        for(size_t j=0; j<circles.size(); j++) {
            Point pt1(circles.at(i)[0], circles.at(i)[1]);
            Point pt2(circles.at(j)[0], circles.at(j)[1]);
            line(img, pt1, pt2, Scalar(128, 128, 128), 2);
        }
    }

    imshow("input", img);
    waitKey(0);
}

