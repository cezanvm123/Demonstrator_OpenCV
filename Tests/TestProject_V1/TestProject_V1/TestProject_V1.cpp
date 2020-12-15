// TestProject_V1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Opencv C++ Example of Operation on Arrays:absdiff  
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>

#include "Kernel.hpp"

using namespace cv;
using namespace std;

#include <iostream>


int main()
{
   
    

    Mat image1,greyMat;

   // image1 = imread("D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\Checkerboard.png", IMREAD_COLOR);
    image1  = imread("D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\pi.png", IMREAD_COLOR);

    cvtColor(image1, greyMat, cv::COLOR_BGR2GRAY);
    namedWindow("Display window gray", WINDOW_AUTOSIZE);
    imshow("Display window gray", greyMat);


    //*********** line detection

    int lineData[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 }; // line detection kernel data
    Kernel* lineKernel = new Kernel();
    lineKernel->initKernel(lineData, 3);
    lineKernel->printKernel();

    cv::Mat lineOutput(cv::Size(greyMat.cols, greyMat.rows), CV_8UC1);
    lineOutput = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    lineKernel->calculateImage(greyMat, lineOutput);  // actual calculation
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    std::cout << time / std::chrono::milliseconds(1) << "ms to run.\n";

    

    namedWindow("Display window lineOutput", WINDOW_AUTOSIZE);
    imshow("Display window lineOutput", lineOutput);



    //********* gausian blur 3x3 *************

    int gaussian3Data[9] = { 1,2,1,2,4,2,1,2,1 }; // gausian blur kernel data
    Kernel* gaussian3Kernel = new Kernel();
    gaussian3Kernel->initKernel(gaussian3Data, 3);
    gaussian3Kernel->setDivider(16);
    gaussian3Kernel->printKernel();

    cv::Mat gaussian3Output(cv::Size(greyMat.cols, greyMat.rows), CV_8UC1);
    gaussian3Output = 0;
    gaussian3Kernel->calculateImage(greyMat, gaussian3Output);  // actual calculation

    namedWindow("Display window gaussian3Output", WINDOW_AUTOSIZE);
    imshow("Display window gaussian3Output", gaussian3Output);



    //********* gausian blur 5x5 *************

    //int gaussian5Data[25] = { 1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1 }; // gausian blur kernel data
    //Kernel* gaussian5Kernel = new Kernel_3X3();
    //gaussian5Kernel->initKernel(gaussian5Data, 5);
    //gaussian5Kernel->setDivider(256);
    //gaussian5Kernel->printKernel();

    //cv::Mat gaussian5Output(cv::Size(greyMat.cols, greyMat.rows), CV_8UC1);
    //gaussian5Output = 0;
    //gaussian5Kernel->calculateImage(greyMat, gaussian5Output);  // actual calculation

    //namedWindow("Display window gaussian5Output", WINDOW_AUTOSIZE);
    //imshow("Display window gaussian5Output", gaussian5Output);



    // ****** guassian 5x5 15 times on the same image just for fun
    //cv::Mat gaussian5Output_2(cv::Size(gaussian5Output.cols, gaussian5Output.rows), CV_8UC1);
    //gaussian5Output_2 = gaussian5Output;

    //for (int i = 0; i < 15; i++)
    //{
    //    gaussian5Kernel->calculateImage(gaussian5Output, gaussian5Output_2);  // actual calculation

    //    
    //}

    //namedWindow("Display window gaussian5Output_2", WINDOW_AUTOSIZE);
    //imshow("Display window gaussian5Output_2", gaussian5Output_2);
    //





    waitKey(0);
    return 0;
}
