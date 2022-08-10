#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{ 
    Mat img = imread("models.jpg");

    namedWindow("image", WINDOW_KEEPRATIO);
    namedWindow("result", WINDOW_KEEPRATIO);

    Mat thresresult;
    cvtColor(img, thresresult, COLOR_BGR2GRAY);
    threshold(thresresult, thresresult, 30, 255, THRESH_OTSU);

    cv::imwrite("models_threshold.jpg", thresresult);

    return 0;
}