#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);
    if(!cap.isOpened()) return -1;

    Mat edges;
    //namedWindow("frame",WINDOW_KEEPRATIO);
    //namedWindow("Thres",WINDOW_KEEPRATIO);


    //loading models
    vector< Mat > models_img;
    vector< string > models_label;

    // get models img at 0 degrees
    models_img.push_back(imread("images(0)/a.png",0));
    models_img.push_back(imread("images(0)/b.png",0));
    models_img.push_back(imread("images(0)/c.png",0));
    models_img.push_back(imread("images(0)/d.png",0));
    models_img.push_back(imread("images(0)/e.png",0));
    models_img.push_back(imread("images(0)/f.png",0));
    models_img.push_back(imread("images(0)/g.png",0));
    models_img.push_back(imread("images(0)/h.png",0));

    // get models img at -30 degrees
    vector< Mat > models_img_30_1;

    models_img_30_1.push_back(imread("images(-30)/a_-30.png",0));
    models_img_30_1.push_back(imread("images(-30)/b_-30.png",0));
    models_img_30_1.push_back(imread("images(-30)/c_-30.png",0));
    models_img_30_1.push_back(imread("images(-30)/d_-30.png",0));
    models_img_30_1.push_back(imread("images(-30)/e_-30.png",0));
    models_img_30_1.push_back(imread("images(-30)/f_-30.png",0));
    models_img_30_1.push_back(imread("images(-30)/g_-30.png",0));
    models_img_30_1.push_back(imread("images(-30)/h_-30.png",0));

    // get models img at 30 degrees
    vector< Mat > models_img_30_2;

    models_img_30_2.push_back(imread("images(30)/a_30.png",0));
    models_img_30_2.push_back(imread("images(30)/b_30.png",0));
    models_img_30_2.push_back(imread("images(30)/c_30.png",0));
    models_img_30_2.push_back(imread("images(30)/d_30.png",0));
    models_img_30_2.push_back(imread("images(30)/e_30.png",0));
    models_img_30_2.push_back(imread("images(30)/f_30.png",0));
    models_img_30_2.push_back(imread("images(30)/g_30.png",0));
    models_img_30_2.push_back(imread("images(30)/h_30.png",0));

    // get models img at -60 degrees
    vector< Mat > models_img_60_1;

    models_img_60_1.push_back(imread("images(-60)/a_-60.png",0));
    models_img_60_1.push_back(imread("images(-60)/b_-60.png",0));
    models_img_60_1.push_back(imread("images(-60)/c_-60.png",0));
    models_img_60_1.push_back(imread("images(-60)/d_-60.png",0));
    models_img_60_1.push_back(imread("images(-60)/e_-60.png",0));
    models_img_60_1.push_back(imread("images(-60)/f_-60.png",0));
    models_img_60_1.push_back(imread("images(-60)/g_-60.png",0));
    models_img_60_1.push_back(imread("images(-60)/h_-60.png",0));

    // get models img at 60 degrees
    vector< Mat > models_img_60_2;

    models_img_60_2.push_back(imread("images(60)/a_60.png",0));
    models_img_60_2.push_back(imread("images(60)/b_60.png",0));
    models_img_60_2.push_back(imread("images(60)/c_60.png",0));
    models_img_60_2.push_back(imread("images(60)/d_60.png",0));
    models_img_60_2.push_back(imread("images(60)/e_60.png",0));
    models_img_60_2.push_back(imread("images(60)/f_60.png",0));
    models_img_60_2.push_back(imread("images(60)/g_60.png",0));
    models_img_60_2.push_back(imread("images(60)/h_60.png",0));

    // get models img at -90 degrees
    vector< Mat > models_img_90_1;

    models_img_90_1.push_back(imread("images(-90)/a_-90.png",0));
    models_img_90_1.push_back(imread("images(-90)/b_-90.png",0));
    models_img_90_1.push_back(imread("images(-90)/c_-90.png",0));
    models_img_90_1.push_back(imread("images(-90)/d_-90.png",0));
    models_img_90_1.push_back(imread("images(-90)/e_-90.png",0));
    models_img_90_1.push_back(imread("images(-90)/f_-90.png",0));
    models_img_90_1.push_back(imread("images(-90)/g_-90.png",0));
    models_img_90_1.push_back(imread("images(-90)/h_-90.png",0));

    // get models img at 90 degrees
    vector< Mat > models_img_90_2;

    models_img_90_2.push_back(imread("images(90)/a_90.png",0));
    models_img_90_2.push_back(imread("images(90)/b_90.png",0));
    models_img_90_2.push_back(imread("images(90)/c_90.png",0));
    models_img_90_2.push_back(imread("images(90)/d_90.png",0));
    models_img_90_2.push_back(imread("images(90)/e_90.png",0));
    models_img_90_2.push_back(imread("images(90)/f_90.png",0));
    models_img_90_2.push_back(imread("images(90)/g_90.png",0));
    models_img_90_2.push_back(imread("images(90)/h_90.png",0));    


    models_label.push_back("a");
    models_label.push_back("b");
    models_label.push_back("c");
    models_label.push_back("d");
    models_label.push_back("e");
    models_label.push_back("f");
    models_label.push_back("g");
    models_label.push_back("h");

    for(int i=0;i<models_img.size();i++) {
        cv::resize(models_img.at(i), models_img.at(i), cv::Size(64,64), 0, 0, INTER_NEAREST);
        cv::resize(models_img_30_1.at(i), models_img_30_1.at(i), cv::Size(64,64), 0, 0, INTER_NEAREST);
        cv::resize(models_img_30_2.at(i), models_img_30_2.at(i), cv::Size(64,64), 0, 0, INTER_NEAREST);
        cv::resize(models_img_60_1.at(i), models_img_60_1.at(i), cv::Size(64,64), 0, 0, INTER_NEAREST);
        cv::resize(models_img_60_2.at(i), models_img_60_2.at(i), cv::Size(64,64), 0, 0, INTER_NEAREST);
    }

    vector<Mat> models_img_rotated;

    for(;;)
    {
        //capturing image from camera
        Mat frame;
        cap >> frame;

        //thresholding
        Mat thresresul;
        cvtColor( frame, thresresul, COLOR_BGR2GRAY );
        threshold( thresresul, thresresul, 30, 255, THRESH_OTSU);

        //Dectecting countors
        vector< vector<cv::Point> > contourShape;
        vector<Vec4i> hierarchy;
        findContours( thresresul, contourShape, RETR_TREE, CHAIN_APPROX_SIMPLE );

        //vector of subimges
        vector< Mat > subimages;
        vector< Rect > subimages_pos;

        //drawing
        Mat drawing = Mat::zeros( frame.size(), CV_8UC3 );
        for( int i = 0; i < contourShape.size(); i++ )
        {
            if(contourShape.at(i).size() > 30)
            {
                drawContours( drawing, contourShape, (int)i, Scalar(rand()%255,rand()%255,rand()%255), 2, LINE_8);

                //extract subimages
                //TODO do it latter with cv::Moments -- see BoundingBox
                int minx,miny,maxx,maxy;
                minx=miny=999999; maxx=maxy=-miny;
                for(int j=0; j<contourShape.at(i).size(); j++)
                {
                    Point pt = contourShape.at(i).at(j);
                    if(pt.x < minx) minx = pt.x;
                    if(pt.y < miny) miny = pt.y;
                    if(pt.x > maxx) maxx = pt.x;
                    if(pt.y > maxy) maxy = pt.y;
                }

                Mat subImg = thresresul(Rect(minx,miny, maxx-minx,maxy-miny));

                subimages.push_back(subImg);
                subimages_pos.push_back(Rect(minx,miny, maxx-minx,maxy-miny));
            }
        }

        //*** classification starts here from vector subimages;

        //preenchendo um bufferzinho
        unsigned int sizeBuffer = 10;
        vector< Mat > bufferSubImages;

        for(int i=0; i< subimages.size(); i++)
        {
            Mat resized;
            cv::resize(subimages.at(i), resized, cv::Size(64,64), 0, 0, INTER_NEAREST);

            //classifier 0 degrees
            for( int j=0; j<models_img.size(); j++)
            {
                Mat subtraction = abs(resized - models_img.at(j));

                //how many pixels matching
                float acum=0;
                for(int m=0; m<subtraction.rows; m++)
                {
                    for(int n=0; n<subtraction.cols; n++)
                    {
                        if(subtraction.at<unsigned char>(m,n) > 0) acum++;
                    }
                }
                float similarity = 1 - acum / (subtraction.rows*subtraction.cols);
                if(similarity > 0.85)
                {
                    Rect rect = subimages_pos.at(i);
                    putText(frame, models_label.at(j), Point(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255), 3);
                }
                //if(waitKey(100) >= 0) break;
            }

            //classifier -30 degrees
            for( int j=0; j<models_img_30_1.size(); j++)
            {
                Mat subtraction = abs(resized - models_img_30_1.at(j));

                //how many pixels matching
                float acum=0;
                for(int m=0; m<subtraction.rows; m++)
                {
                    for(int n=0; n<subtraction.cols; n++)
                    {
                        if(subtraction.at<unsigned char>(m,n) > 0) acum++;
                    }
                }
                float similarity = 1 - acum / (subtraction.rows*subtraction.cols);
                if(similarity > 0.82)
                {
                    Rect rect = subimages_pos.at(i);
                    putText(frame, models_label.at(j), Point(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255), 3);
                }
                //if(waitKey(100) >= 0) break;
            }

            //classifier -60 degrees
            for( int j=0; j<models_img_60_1.size(); j++)
            {
                Mat subtraction = abs(resized - models_img_60_1.at(j));

                //how many pixels matching
                float acum=0;
                for(int m=0; m<subtraction.rows; m++)
                {
                    for(int n=0; n<subtraction.cols; n++)
                    {
                        if(subtraction.at<unsigned char>(m,n) > 0) acum++;
                    }
                }
                float similarity = 1 - acum / (subtraction.rows*subtraction.cols);
                if(similarity > 0.82)
                {
                    Rect rect = subimages_pos.at(i);
                    putText(frame, models_label.at(j), Point(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255), 3);
                }
                //if(waitKey(100) >= 0) break;
            }

            //classifier 30 degrees
            for( int j=0; j<models_img_30_2.size(); j++)
            {
                Mat subtraction = abs(resized - models_img_30_2.at(j));

                //how many pixels matching
                float acum=0;
                for(int m=0; m<subtraction.rows; m++)
                {
                    for(int n=0; n<subtraction.cols; n++)
                    {
                        if(subtraction.at<unsigned char>(m,n) > 0) acum++;
                    }
                }
                float similarity = 1 - acum / (subtraction.rows*subtraction.cols);
                if(similarity > 0.82)
                {
                    Rect rect = subimages_pos.at(i);
                    putText(frame, models_label.at(j), Point(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255), 3);
                }
                //if(waitKey(100) >= 0) break;
            }

            //classifier 60 degrees
            for( int j=0; j<models_img_60_2.size(); j++)
            {
                Mat subtraction = abs(resized - models_img_60_2.at(j));

                //how many pixels matching
                float acum=0;
                for(int m=0; m<subtraction.rows; m++)
                {
                    for(int n=0; n<subtraction.cols; n++)
                    {
                        if(subtraction.at<unsigned char>(m,n) > 0) acum++;
                    }
                }
                float similarity = 1 - acum / (subtraction.rows*subtraction.cols);
                if(similarity > 0.82)
                {
                    Rect rect = subimages_pos.at(i);
                    putText(frame, models_label.at(j), Point(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255), 3);
                }
                //if(waitKey(100) >= 0) break;
            }

            //from here... DISPLAY
            bufferSubImages.push_back(resized);
            //limitar o tamanho para sempre comportar o numero maximo de subimagens a mostrar
            if(bufferSubImages.size() > sizeBuffer)
                bufferSubImages.erase(bufferSubImages.begin());

            //mostrando last N imagens no mesmo
            Mat allSubImages = Mat::zeros( cv::Size(64*sizeBuffer,64), CV_8UC1);
            for(int j=0; j< bufferSubImages.size(); j++)
            {
                bufferSubImages.at(j).copyTo(allSubImages(Rect(64*j,0,bufferSubImages.at(j).cols, bufferSubImages.at(j).rows)));

                //generating thumb images to models
                static int index = 1;
                stringstream sst; sst << "models/output_" << index++ << ".bmp";
                imwrite( sst.str(), bufferSubImages.at(j) );
            }
            if(waitKey(1) >= 0) break;
        }

        imshow("frame", frame);
        
        if(waitKey(30) >= 0) break;
    }

    return 0;
}
