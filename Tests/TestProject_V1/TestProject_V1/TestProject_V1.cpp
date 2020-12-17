// TestProject_V1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Opencv C++ Example of Operation on Arrays:absdiff  
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>

#include "Kernel.hpp"

#include "Test.hpp"
#include "Kernel_Image.hpp"
#include "SeparableKernel_Image.hpp"


using namespace cv;
using namespace std;

#include <iostream>


int main()
{
   
	{

		float data[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
		Test* kernel = new Kernel_Image(3,
			data,
			1,
			false,
			"line test, image, kernel",
			"C:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\pi.png");
		kernel->runTest();

	}

	{

		float h_vector[3] = { -1,0,1 }; // horizontal
		float v_vector[3] = { 1,2,1 }; // vertical 
		Test* kernel = new SeparableKernel_Image(3,
			h_vector,
			v_vector,
			1,
			false,
			"line test, image, separable",
			"C:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\pi.png");
		kernel->runTest();

	}

	{

		float data[9] = { 0.077847,  0.123317,  0.077847,
						  0.123317,  0.195346,  0.123317,
			              0.077847,  0.123317,  0.077847 };

		Test* kernel = new Kernel_Image(3,
			data,
			1,
			true,
			"Gaussian, image, kernel",
			"C:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\pi.png");
		kernel->runTest();

	}

	{

		float h_vector[3] = { 0.27901, 0.44198, 0.27901 }; // horizontal
		float v_vector[3] = { 0.27901, 0.44198, 0.27901 }; // vertical 
		Test* kernel = new SeparableKernel_Image(3,
			h_vector,
			v_vector,
			1,
			true,
			"Gaussian, image, separable",
			"C:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\pi.png");
		kernel->runTest();

	}


    





    waitKey(0);
    return 0;
}
