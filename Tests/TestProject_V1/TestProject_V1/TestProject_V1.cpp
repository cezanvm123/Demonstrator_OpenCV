// TestProject_V1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Opencv C++ Example of Operation on Arrays:absdiff  
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>


#include "Test.hpp"
#include "Kernel_Image.hpp"
#include "SeparableKernel_Image.hpp"
#include "SeparableKernel_Video.hpp"


using namespace cv;
using namespace std;

#include <iostream>


int main()
{
   
	String imgPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\openCV_240.png";
	String vidPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\OpenCV_vid.mp4";
	{

		float data[9] = { -1,  -1,  -1,
						  -1,   8,  -1,
						  -1,  -1,  -1 };
		Test* kernel = new Kernel_Image(3,
			data,
			1,
			false,
			"kernel, line test, image",
			imgPath);
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
			"separable, line test, image",
			imgPath);
		kernel->runTest();

	}

	{

		float data[9] = { 0.077847,  0.123317,  0.077847,
						  0.123317,  0.195346,  0.123317,
			              0.077847,  0.123317,  0.077847 };

		Test* kernel = new Kernel_Image(3,
			data,
			1,
			false,
			"kernel, Gaussian, image",
			imgPath);
		kernel->runTest();

	}

	{

		float h_vector[3] = { 0.27901, 0.44198, 0.27901 }; // horizontal
		float v_vector[3] = { 0.27901, 0.44198, 0.27901 }; // vertical 
		Test* kernel = new SeparableKernel_Image(3,
			h_vector,
			v_vector,
			1,
			false,
			"separable, Gaussian, image",
			imgPath);
		kernel->runTest();

	}


	if (true)  // used to disable the test
	{

		float h_vector[3] = { -1,0,1 }; // horizontal
		float v_vector[3] = { 1,2,1 }; // vertical 
		Test* kernel = new SeparableKernel_Video(3,
			h_vector,
			v_vector,
			1,
			true,
			871,
			"separable, line test, video",
			vidPath);
		kernel->runTest();

	}

	if(true)  // used to disable the test
	{

		float h_vector[3] = { 0.27901, 0.44198, 0.27901 }; // horizontal
		float v_vector[3] = { 0.27901, 0.44198, 0.27901 }; // vertical 

		Test* kernel = new SeparableKernel_Video(3,
			h_vector,
			v_vector,
			1,
			true,
			871,
			"separable, Gaussian, video",
			vidPath);
		kernel->runTest();

	}


    





    waitKey(0);
    return 0;
}
