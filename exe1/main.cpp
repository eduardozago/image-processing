#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    Mat img = imread("s_12003.jpg");
    imshow("Image", img);
    waitKey(0);
    
    return 0;
    
}
