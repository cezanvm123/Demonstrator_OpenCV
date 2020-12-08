// TestProject_V1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Opencv C++ Example of Operation on Arrays:absdiff  
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#include <iostream>

enum Location
{
    IS_ZERO,
    IS_BETWEEN,
    IS_MAX
};

void setupEdgeKernel(int** kernel, size_t rows, size_t cols)
{

    kernel[0][0] = -1;
    kernel[0][1] = -1;
    kernel[0][2] = -1;
    kernel[1][0] = -1;
    kernel[1][1] = 8;
    kernel[1][2] = -1;
    kernel[2][0] = -1;
    kernel[2][1] = -1;
    kernel[2][2] = -1;


    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            std::cout << kernel[r][c] << " ";

        }
        std::cout << std::endl;
    }
}


//void determineLoc(Location& l, int &val, int &max)
//{
//    if (val == 0)
//    {
//        l = Location::IS_ZERO;
//    }
//    else if (val == max - 1)
//    {
//        l = Location::IS_MAX;
//    }
//    else
//    {
//        if (l != Location::IS_BETWEEN) // check to not keep setting the value, might perform worse
//        {
//            l = Location::IS_BETWEEN;
//        }
//    }
//}


int main()
{
    int **kernel_3;
    kernel_3 = new int* [10];
    for (int i = 0; i < 10; i++)
        kernel_3[i] = new int[10];

    int kernel_5[5][5];
    

    Mat image1, image2, dst;

    //image1 = imread("D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\OpenCV.png", IMREAD_COLOR);
    //if (!image1.data) { printf("Error loading image1 \n"); return -1; }



    image1  = imread("D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\PI.png", IMREAD_COLOR);


    Mat greyMat, colorMat;
    cvtColor(image1, greyMat, cv::COLOR_BGR2GRAY);



    namedWindow("Display window gray", WINDOW_AUTOSIZE);
    imshow("Display window gray", greyMat);   



    // kernel calculation
    // calculations:
        // (row-1, col-1) * (kernel[0][0])
        // (row-1, col) * (kernel[0][1])
        // (row-1, col+1) * (kernel[0][2])

        // (row, col-1) * (kernel[1][0])
        // (row, col) * (kernel[1][1])    // middle
        // (row, col+1) * (kernel[1][2])

        // (row+1, col-1) * (kernel[2][0])
        // (row+1, col) * (kernel[2][1])
        // (row+1, col+1) * (kernel[2][2])

    cv::Mat test(cv::Size( greyMat.cols, greyMat.rows), CV_8UC1);
    test = 0;

    setupEdgeKernel(kernel_3, 3, 3);



    // intitialized above the loops to improve performance and
    // function calls
    int total = 0;
    int c = 0;
    int r = 0;

    int rows = greyMat.rows -1;
    int cols = greyMat.cols -1;

    Location rowLoc = Location::IS_ZERO;
    Location colLoc = Location::IS_ZERO;

    for (r = 1; r <= rows-1; r++)
    {
      //  determineLoc(rowLoc, r, rows);
        for (c = 1; c <= cols-1; c++)
        {
           // determineLoc(colLoc, c, cols);

            total = (int)greyMat.at<uchar>(r, c) * kernel_3[1][1]; // middle calculation (will never throw)

                total += (int)greyMat.at<uchar>(r-1, c-1) * kernel_3[0][0];
                total += (int)greyMat.at<uchar>(r-1, c) * kernel_3[0][1];
                total += (int)greyMat.at<uchar>(r-1, c+1) * kernel_3[0][2];

                total += (int)greyMat.at<uchar>(r, c - 1) * kernel_3[1][0];
                total += (int)greyMat.at<uchar>(r, c + 1) * kernel_3[1][2];

                total += (int)greyMat.at<uchar>(r+1, c - 1) * kernel_3[2][0];
                total += (int)greyMat.at<uchar>(r+1, c) * kernel_3[2][1];
                total += (int)greyMat.at<uchar>(r+1, c + 1) * kernel_3[2][2];


                test.at<uchar>(Point(c, r)) = total;
        }
    }
   


    namedWindow("Line", WINDOW_AUTOSIZE);
    imshow("Line", test);


    waitKey(0);
    return 0;
}
