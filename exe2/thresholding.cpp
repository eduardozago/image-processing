#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat img = imread("../CTImages/CT_head2.jpg");

    Mat result = img.clone();

    namedWindow("Image", WINDOW_KEEPRATIO);
    namedWindow("Result", WINDOW_KEEPRATIO);

    int th = 100;
    int alpha = 80;

    createTrackbar("Threshold", "Result", &th, 255);
    createTrackbar("Alpha", "Result", &alpha, 255);

    while(true) {
        for(size_t i=0; i<img.rows; i++) {
            for(size_t j=0; j<img.cols; j++) {
                Vec3b pxRef = img.at<Vec3b>(i,j);

                if(pxRef[0] > th - alpha && pxRef[0] < th + alpha) {
                    result.at<Vec3b>(i,j)[0] = 255;
                    result.at<Vec3b>(i,j)[1] = 255;
                    result.at<Vec3b>(i,j)[2] = 255;
                } else {
                    result.at<Vec3b>(i,j)[0] = 0;
                    result.at<Vec3b>(i,j)[1] = 0;
                    result.at<Vec3b>(i,j)[2] = 0;
                }
            }
        }

        imshow("Image", img);
        imshow("Result", result);
    }

    waitKey(50);

    return 0;
}