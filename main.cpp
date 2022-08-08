#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("CTImages/CT_head1.jpg");
    Mat result = img.clone();

    namedWindow("image", WINDOW_KEEPRATIO);
    namedWindow("result", WINDOW_KEEPRATIO);

    int th = 100;
    int alpha = 80;

    createTrackbar("Threshold", "result", &th, 255);
    createTrackbar("Alpha", "result", &alpha, 255);

    while (true) {

        for(size_t i=0; i<img.rows; i++)
        {
            for(size_t j=0; j<img.cols; j++)
            {
                Vec3b pxRef = img.at<Vec3b>(i,j);

                if(pxRef[0] < th+alpha && pxRef[0] > th-alpha)
                {
                    result.at<Vec3b>(i,j)[0] = 255;
                    result.at<Vec3b>(i,j)[1] = 255;
                    result.at<Vec3b>(i,j)[2] = 255;
                }
                else
                {
                    result.at<Vec3b>(i,j)[0] = 0;
                    result.at<Vec3b>(i,j)[1] = 0;
                    result.at<Vec3b>(i,j)[2] = 0;
                }
            }
        }
        imshow("image", img);
        imshow("result", result);
        waitKey(50);

    }

    waitKey(0);

    return 0;
}