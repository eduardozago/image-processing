#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("s_plane.png");
/*
    Mat img_gray;
    cvtColor( img, img_gray, COLOR_BGR2GRAY);

    Mat sobelx, sobely, G;
    Sobel(img_gray, sobelx, CV_32F, 1, 0, 3);
    Sobel(img_gray, sobely, CV_32F, 0, 1, 3);

    convertScaleAbs(sobelx, sobelx);
    convertScaleAbs(sobely, sobely);
    addWeighted( sobelx, 0.5, sobely, 0.5, 0, G);

    imshow("input image", img_gray);
    imshow("x", sobelx);
    imshow("y", sobely);
    imshow("G", G);
*/
    Mat img_blur, img_canny, img_edges;

    //Canny( img_gray, img_r1, 1, 50, 3 );

    //lur( img, img_blur, Size(3,3));
    Canny( img, img_edges, 1, 50, 3 );

    vector<Vec4i> lines;
    HoughLinesP( img_edges, lines, 1, CV_PI/180, 10, 5, 10);

    for( size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines.at(i);
        line(img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
    }

    imshow("image", img);
    //imshow("r1", img_r1);
    imshow("result", img_edges);

    waitKey(0);
}