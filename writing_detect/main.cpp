#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{ 

    // Loading models
    vector< Mat > models_img;
    vector< string > models_label;

    models_img.push_back(imread("models/a.jpg",0));
    models_img.push_back(imread("models/b.jpg",0));
    models_img.push_back(imread("models/c.jpg",0));
    models_img.push_back(imread("models/d.jpg",0));
    models_img.push_back(imread("models/e.jpg",0));
    models_img.push_back(imread("models/f.jpg",0));
    models_img.push_back(imread("models/g.jpg",0));
    models_img.push_back(imread("models/h.jpg",0));
    models_img.push_back(imread("models/i.jpg",0));
    models_img.push_back(imread("models/j.jpg",0));
    models_img.push_back(imread("models/k.jpg",0));
    models_img.push_back(imread("models/l.jpg",0));
    models_img.push_back(imread("models/m.jpg",0));
    models_img.push_back(imread("models/n.jpg",0));
    models_img.push_back(imread("models/o.jpg",0));
    models_img.push_back(imread("models/p.jpg",0));
    models_img.push_back(imread("models/q.jpg",0));
    models_img.push_back(imread("models/r.jpg",0));

    models_label.push_back("a");
    models_label.push_back("b");
    models_label.push_back("c");
    models_label.push_back("d");
    models_label.push_back("e");
    models_label.push_back("f");
    models_label.push_back("g");
    models_label.push_back("h");
    models_label.push_back("i");
    models_label.push_back("j");
    models_label.push_back("k");
    models_label.push_back("l");
    models_label.push_back("m");
    models_label.push_back("m");
    models_label.push_back("o");
    models_label.push_back("p");
    models_label.push_back("q");
    models_label.push_back("r");

    // Resize all models to 64x64 
    for(int i=0;i<models_img.size();i++) {
        cv::resize(models_img.at(i), models_img.at(i), cv::Size(64,64), 0, 0, INTER_NEAREST);
    }

    // Insert img
    string input_img;
    cout << "Input image: " << endl;
    getline(cin, input_img);

    Mat img = imread(input_img);

    // Thresholding 
    Mat thresresult;
    cvtColor(img, thresresult, COLOR_BGR2GRAY);
    threshold(thresresult, thresresult, 30, 255, THRESH_OTSU);

    // Dectecting countors
    vector< vector<cv::Point> > contourShape;
    vector<Vec4i> hierarchy;
    findContours( thresresult, contourShape, RETR_TREE, CHAIN_APPROX_SIMPLE );

    // Vector of subimges
    vector< Mat > subimages;
    vector< Rect > subimages_pos;

    // Drawing
    Mat drawing = Mat::zeros( img.size(), CV_8UC3 );
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

            Mat subImg = thresresult(Rect(minx,miny, maxx-minx,maxy-miny));

            subimages.push_back(subImg);
            subimages_pos.push_back(Rect(minx,miny, maxx-minx,maxy-miny));
        }
    }

    // classification

    unsigned int sizeBuffer = 10;
    vector< Mat > bufferSubImages;

    vector<string> text;
    vector<Point> positions;

    for(int i=0; i< subimages.size(); i++)
    {
        Mat resized;
        cv::resize(subimages.at(i), resized, cv::Size(64,64), 0, 0, INTER_NEAREST);

        for( int j=0; j<models_img.size(); j++)
        {
            Mat subtraction = abs(resized - models_img.at(j));

            // how many pixels matching
            float acum=0;
            for(int m=0; m<subtraction.rows; m++)
            {
                for(int n=0; n<subtraction.cols; n++)
                {
                    if(subtraction.at<unsigned char>(m,n) > 0) acum++;
                }
            }
            float similarity = 1 - acum / (subtraction.rows*subtraction.cols);
            if(similarity > 0.78)
            {
                // Get text and position
                Rect rect = subimages_pos.at(i);
                text.push_back(models_label.at(j));
                positions.push_back(Point(rect.x, rect.y));
                putText(img, models_label.at(j), Point(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255), 3);
            }
        }
    }

    int pos_tmp = positions.at(0).x;
    string finalText;

    // Order text
    for(int i=1;i<positions.size();i++){
        if(pos_tmp > positions.at(i).x) {
            string tmp_text = text.at(i);
            text.at(i) = text.at(i-1); 
            text.at(i-1) = tmp_text;
            pos_tmp = positions.at(i).x;
        } 
    }

    // Get string
    for(int i=0;i<text.size();i++) {
        finalText = finalText + text.at(i);
    }

    cout << "Result: " << finalText << endl;

    cv::resize(img, img, cv::Size(604,806), 0, 0, INTER_NEAREST);
    
    namedWindow("result", WINDOW_KEEPRATIO);
    imshow("result", img);
    waitKey(0);

    return 0;
}