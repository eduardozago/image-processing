#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("plane.bmp");
    Mat result = img.clone();

    int kernel[3][3];
    int sumkernel = 16;
    // detecção em x
    // kernel[0][0]=-1; kernel[0][1]=0; kernel[0][2]=1;
    // kernel[1][0]=-2; kernel[1][1]=0; kernel[1][2]=2;
    // kernel[2][0]=-1; kernel[2][1]=0; kernel[2][2]=1;

    // detecção em y
    kernel[0][0]=-1; kernel[0][1]=-2; kernel[0][2]=-1;
    kernel[1][0]=0; kernel[1][1]=0; kernel[1][2]=0;
    kernel[2][0]=-1; kernel[2][1]=2; kernel[2][2]=1;

    for(size_t i=1; i<img.rows-1; i++)
    {
        for(size_t j=1; j<img.cols-1; j++)
        {
            //reading
            Vec3b px00 = img.at<Vec3b>(i-1,j-1);
            Vec3b px01 = img.at<Vec3b>(i-1,j);
            Vec3b px02 = img.at<Vec3b>(i-1,j+1);

            Vec3b px10 = img.at<Vec3b>(i,j-1);
            Vec3b px11 = img.at<Vec3b>(i,j);
            Vec3b px12 = img.at<Vec3b>(i,j+1);

            Vec3b px20 = img.at<Vec3b>(i+1,j-1);
            Vec3b px21 = img.at<Vec3b>(i+1,j);
            Vec3b px22 = img.at<Vec3b>(i+1,j+1);

            int impulse =
            px00[0]*kernel[0][0] + px01[0]*kernel[0][1] + px02[0]*kernel[0][2] +
            px10[0]*kernel[1][0] + px11[0]*kernel[1][1] + px12[0]*kernel[1][2] +
            px20[0]*kernel[2][0] + px21[0]*kernel[2][1] + px22[0]*kernel[2][2];
            impulse = impulse / 1;

            //writing
            result.at<Vec3b>(i,j)[0] = abs(impulse);
            result.at<Vec3b>(i,j)[1] = abs(impulse);
            result.at<Vec3b>(i,j)[2] = abs(impulse);
        }
    }

    imshow("image", img);
    imshow("result", result);

    waitKey(0);

    return 0;
}