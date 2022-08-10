#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{

    Mat src = imread("a/all.png");
    double angle = -60;

    Point2f center((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);

    Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);

    Mat rotated_image;

    warpAffine(src, rotated_image, rotation_matix, src.size());

    //models_img_rotated_60_1.push_back(rotated_image);
    //models_img.push_back(rotated_image);

    //cv::resize(rotated_image, rotated_image, cv::Size(64,64), 0, 0, INTER_NEAREST);

    //namedWindow("rotation 2",WINDOW_KEEPRATIO);
    cv::imwrite("images(-60)/rotation_-60.png", rotated_image);
    //imshow("rotation 2", rotated_image);
}