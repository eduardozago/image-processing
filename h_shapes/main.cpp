#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);
    if(!cap.isOpened()) return 1;

    namedWindow("Device Frame", WINDOW_KEEPRATIO);
    namedWindow("Threshold", WINDOW_KEEPRATIO);
    namedWindow("Subimage", WINDOW_KEEPRATIO);

    for(;;)
    {
        //read camera
        Mat frame;
        cap >> frame;

        //1. threshold
        Mat framethresh;
        cvtColor(frame, framethresh, COLOR_BGR2GRAY);
        threshold(framethresh, framethresh, 30, 255, THRESH_OTSU);

        //2.find contours
        vector< vector< Point > > listOfContours;
        findContours(framethresh, listOfContours, 1, 1);

        cout << "Number of contours " << listOfContours.size() << endl;

        vector<Mat> extractedShapes;
        vector<Point> extractedPositions;

        //3. extract each contour into a single image
        for(size_t i=0; i<listOfContours.size(); i++)
        {
            //filter shape by perimeter of 50 points
            if(listOfContours.at(i).size() > 50)
            {
                cout << "    Contour id " << i << " -> perimeter : " << listOfContours.at(i).size() << endl;

                drawContours(frame, listOfContours, i, Scalar(rand()%255,rand()%255,rand()%255), 2);

                //find minx miny maxx maxy
                //or use moments
                int minx, miny, maxx, maxy;
                minx=miny=9999999; maxx=maxy=-minx;
                for(size_t j=0; j<listOfContours.at(i).size(); j++)
                {
                    Point pt = listOfContours.at(i).at(j);
                    if(pt.x < minx) minx=pt.x;
                    if(pt.y < miny) miny=pt.y;
                    if(pt.x > maxx) maxx=pt.x;
                    if(pt.y > maxy) maxy=pt.y;
                }
                //get subimage and push_back into a vector
                Mat subimage = framethresh(Rect(minx,miny,maxx-minx,maxy-miny));
                extractedShapes.push_back(subimage);
                extractedPositions.push_back(Point((minx+maxx)/2, (miny+maxy)/2));
            }
        }

        //4. Comparar as formas geometricas
        Mat modelA = imread("model_a.bmp", 0);
        for(size_t i=0; i< extractedShapes.size(); i++)
        {
            Mat shape2compare = extractedShapes.at(i);
            //shape2compare -> resize 64x64
            resize(shape2compare, shape2compare, Size(64,64),0,0,INTER_NEAREST);

            Mat differences = abs(shape2compare-modelA);

            //pseudo histogram, how many pixels do we have
            float acum=0;
            for(size_t m=0; m<differences.rows; m++)
                for(size_t n=0; n<differences.cols; n++)
                    if(differences.at<unsigned char>(m,n) > 0) acum++;

            //float similarity = 1 - acum/64*64;
            //cout << "sim: " << similarity << endl;
            if(acum < 50)
            {
                Point pt = extractedPositions.at(i);
                putText(frame, "A", pt, FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255), 3);
                waitKey(30);
            }
        }

        //show results
        imshow("Device Frame", frame);
        imshow("Threshold", framethresh);
        if(waitKey(30) > 0) break;
    }
    return 0;
}