#include "convolution.hpp"

int main()
{
    Mat img = imread("p2.jpg");
    Mat result = Mat::zeros(img.size(), img.type());

    int kernel[3][3];
    int sumkernel = 16;
    //kernel para calculo de borda em orientacao em x
/*    kernel[0][0]=-1; kernel[0][1]=0; kernel[0][2]=+1;
    kernel[1][0]=-2; kernel[1][1]=0; kernel[1][2]=+2;
    kernel[2][0]=-1; kernel[2][1]=0; kernel[2][2]=+1;*/

    kernel[0][0]=-1; kernel[0][1]=-2; kernel[0][2]=-1;
    kernel[1][0]=0; kernel[1][1]=0; kernel[1][2]=0;
    kernel[2][0]=+1; kernel[2][1]=+2; kernel[2][2]=+1;

/*
    kernel[0][0]=-1; kernel[0][1]=-1; kernel[0][2]=0; kernel[0][3]=+1; kernel[0][4]=+1;
    kernel[1][0]=-1; kernel[1][1]=-1; kernel[1][2]=0; kernel[1][3]=+1; kernel[1][4]=+1;
    kernel[2][0]=-2; kernel[2][1]=-2; kernel[2][2]=0; kernel[2][3]=+2; kernel[2][4]=+2; 
    kernel[3][0]=-1; kernel[3][1]=-1; kernel[3][2]=0; kernel[3][3]=+1; kernel[3][4]=+1; 
    kernel[4][0]=-1; kernel[4][1]=-1; kernel[4][2]=0; kernel[4][3]=+1; kernel[4][4]=+1; 


    //kernel para calculo de borda em orientaçao em y
    kernel[0][0]=-1; kernel[0][1]=-1; kernel[0][2]=-2; kernel[0][3]=-1; kernel[0][4]=-1;
    kernel[1][0]=-1; kernel[1][1]=-1; kernel[1][2]=-2; kernel[1][3]=-1; kernel[1][4]=-1;
    kernel[2][0]=0;  kernel[2][1]=0;  kernel[2][2]=0;  kernel[2][3]=0;  kernel[2][4]=0; 
    kernel[3][0]=+1; kernel[3][1]=+1; kernel[3][2]=+2; kernel[3][3]=+1; kernel[3][4]=+1; 
    kernel[4][0]=+1; kernel[4][1]=+1; kernel[4][2]=+2; kernel[4][3]=+1; kernel[4][4]=+1; 
*/
    for(size_t i=1; i<img.rows-1; i++)
    {
        for(size_t j=1; j<img.cols-1; j++)
        {
            //reading
            /*Vec3b px00 = img.at<Vec3b>(i-1,j-1);
            Vec3b px01 = img.at<Vec3b>(i-1,j-1);
            Vec3b px02 = img.at<Vec3b>(i-1,j);
            Vec3b px03 = img.at<Vec3b>(i-1,j+1);
            Vec3b px04 = img.at<Vec3b>(i-1,j+1);

            Vec3b px10 = img.at<Vec3b>(i,j-1);
            Vec3b px11 = img.at<Vec3b>(i,j-1);
            Vec3b px12 = img.at<Vec3b>(i,j);
            Vec3b px13 = img.at<Vec3b>(i,j+1);
            Vec3b px14 = img.at<Vec3b>(i,j+1);

            Vec3b px20 = img.at<Vec3b>(i+1,j-1);
            Vec3b px21 = img.at<Vec3b>(i+1,j-1);
            Vec3b px22 = img.at<Vec3b>(i+1,j);
            Vec3b px23 = img.at<Vec3b>(i+1,j+1);
            Vec3b px24 = img.at<Vec3b>(i+1,j+1);

            Vec3b px30 = img.at<Vec3b>(i+1,j-1);
            Vec3b px31 = img.at<Vec3b>(i+1,j-1);
            Vec3b px32 = img.at<Vec3b>(i+1,j);
            Vec3b px33 = img.at<Vec3b>(i+1,j+1);
            Vec3b px34 = img.at<Vec3b>(i+1,j+1);

            Vec3b px40 = img.at<Vec3b>(i+1,j-1);
            Vec3b px41 = img.at<Vec3b>(i+1,j-1);
            Vec3b px42 = img.at<Vec3b>(i+1,j);
            Vec3b px43 = img.at<Vec3b>(i+1,j+1);
            Vec3b px44 = img.at<Vec3b>(i+1,j+1);*/

            Vec3b px00 = img.at<Vec3b>(i-1,j-1);
            Vec3b px01 = img.at<Vec3b>(i-1,j);
            Vec3b px02 = img.at<Vec3b>(i-1,j+1);

            Vec3b px10 = img.at<Vec3b>(i,j-1);
            Vec3b px11 = img.at<Vec3b>(i,j);
            Vec3b px12 = img.at<Vec3b>(i,j+1);

            Vec3b px20 = img.at<Vec3b>(i+1,j-1);
            Vec3b px21 = img.at<Vec3b>(i+1,j);
            Vec3b px22 = img.at<Vec3b>(i+1,j+1);
            /*
            int impulse =
            px00[0]*kernel[0][0] + px01[0]*kernel[0][1] + px02[0]*kernel[0][2] + px03[0]*kernel[0][3] + px04[0]*kernel[0][4] +
            px10[0]*kernel[1][0] + px11[0]*kernel[1][1] + px12[0]*kernel[1][2] + px13[0]*kernel[1][3] + px14[0]*kernel[1][4] +
            px20[0]*kernel[2][0] + px21[0]*kernel[2][1] + px22[0]*kernel[2][2] + px23[0]*kernel[2][3] + px24[0]*kernel[2][4] + 
            px30[0]*kernel[3][0] + px31[0]*kernel[3][1] + px32[0]*kernel[3][2] + px33[0]*kernel[3][3] + px34[0]*kernel[3][4] + 
            px40[0]*kernel[4][0] + px41[0]*kernel[4][1] + px42[0]*kernel[4][2] + px43[0]*kernel[4][3] + px44[0]*kernel[4][4];
            impulse = impulse / 1;
            */

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