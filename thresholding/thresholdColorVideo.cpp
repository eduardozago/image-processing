#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "cannot open camera";
        return 1;
    }

    Mat img;
    cap >> img;
    Mat result = img.clone();


    namedWindow("image", WINDOW_KEEPRATIO);
    namedWindow("result", WINDOW_KEEPRATIO);

    Vec3b pxRef;
    pxRef[0]=57; //b
    pxRef[1]=33; //g
    pxRef[2]=184; //r

    int ratio=0;
    createTrackbar("Ratio", "result", &ratio, 255);
    //createTrackbar("Alpha", "result", &alpha, 255);

    while (true) {

        cap >> img;
        result = img.clone();

        for(size_t i=0; i<img.rows; i++)
        {
            for(size_t j=0; j<img.cols; j++)
            {
                Vec3b pxCurr = img.at<Vec3b>(i,j);

                float d = sqrt(
                    (pxRef[0]-pxCurr[0]) * (pxRef[0]-pxCurr[0]) +
                    (pxRef[1]-pxCurr[1]) * (pxRef[1]-pxCurr[1]) +
                    (pxRef[2]-pxCurr[2]) * (pxRef[2]-pxCurr[2]));

                if(d < ratio)
                {
                    result.at<Vec3b>(i,j)[0] = 0;
                    result.at<Vec3b>(i,j)[1] = 255;
                    result.at<Vec3b>(i,j)[2] = 0;
                }
                else
                {
                    //result.at<Vec3b>(i,j)[0] = 0;
                    //result.at<Vec3b>(i,j)[1] = 0;
                    //result.at<Vec3b>(i,j)[2] = 0;
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