// TestProject_V1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Opencv C++ Example of Operation on Arrays:absdiff  
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>


#include "Test.hpp"

#include "DFT.hpp"
#include "Kernel_Image.hpp"
#include "Kernel_Video.hpp"
#include "SeparableKernel_Image.hpp"
#include "SeparableKernel_Video.hpp"

#include "MaskGenerator.hpp"


using namespace cv;
using namespace std;

#include <iostream>


int main()
{
	/* Linux paths
	String roadImg = "TestImages/road.png";

	String imgPath = "TestImages/OpenCV_240.png";
	String vidPath = "TestImages/OpenCV.mp4";
	
	string dftFilterPath = "TestImages/Masks/Mask1_lowpass.png";
	*/

    String roadImg = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\road.png";

	String imgPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\openCV_240.png";
	String vidPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\openCV.mp4";
	
	string dftFilterPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\Masks\\Mask1_lowpass.png";
	
	{
		Test* dftTest = new DFT(true, MaskGenerator::getPerfectHighPass(240, 240, 2) xor MaskGenerator::getPerfectLowPass(240, 240, 7), "DFT test", imgPath);
		dftTest->runTest();
	}
	
//	
//	/*
//	- Gaussian Blur test
//	- kernel and separable kernel
//	- video
//
//*/
//	{
//		float data[9] = { -1,  -1,  -1,
//						  -1,   8,  -1,
//						  -1,  -1,  -1 };
//		Test* kernel = new Kernel_Video(3,
//			data,
//			1,
//			false,
//			1100,
//			"kernel, Gaussian Blur, video",
//			vidPath);
//		kernel->runTest();
//
//
//		float h_vector[3] = { -1,0,1 }; // horizontal
//		float v_vector[3] = { 1,2,1 }; // vertical 
//		Test* sepKernel = new SeparableKernel_Video(3,
//			h_vector,
//			v_vector,
//			1,
//			false,
//			1100,
//			"separable, Gaussian Blur, video",
//			vidPath);
//		sepKernel->runTest();
//
//
//	}
//	
//	
//	/*
//		- Gaussian Blur test 
//		- kernel and separable kernel 
//		- video
//
//	*/
//	{
//		float data[9] = { 0.077847,  0.123317,  0.077847,
//						  0.123317,  0.195346,  0.123317,
//						  0.077847,  0.123317,  0.077847 };
//		Test* kernel = new Kernel_Video(3,
//			data,
//			1,
//			false,
//			1100,
//			"kernel, Gaussian Blur, video",
//			vidPath);
//		kernel->runTest();
//
//
//		float h_vector[3] = { 0.27901, 0.44198, 0.27901 }; // horizontal
//		float v_vector[3] = { 0.27901, 0.44198, 0.27901 }; // vertical 
//		Test* sepKernel = new SeparableKernel_Video(3,
//			h_vector,
//			v_vector,
//			1,
//			false,
//			1100,
//			"separable, Gaussian Blur, video",
//			vidPath);
//		sepKernel->runTest();
//
//
//	}
	
	/*
	- Sharpening test
	- kernel and separable kernel
	- video

*/
	//{
	//	float data[9] = { 0,  -1,  0,
	//					  -1,  5,  -1,
	//					  0,  -1,  0 };
	//	Test* kernel = new Kernel_Video(3,
	//		data,
	//		1,
	//		true,
	//		1100,
	//		"kernel, Sharpening test, video",
	//		vidPath);
	//	kernel->runTest();


	//	float h_vector[3] = { -1, 1, -1}; // horizontal
	//	float v_vector[3] = { 1, 9, 1 }; // vertical 
	//	Test* sepKernel = new SeparableKernel_Video(3,
	//		h_vector,
	//		v_vector,
	//		1,
	//		true,
	//		1100,
	//		"separable, Sharpening test, video",
	//		vidPath);
	//	sepKernel->runTest();


	//}
	//
	
	//{

	//	float data[9] = { -1,  -1,  -1,
	//					  -1,   8,  -1,
	//					  -1,  -1,  -1 };
	//	Test* kernel = new Kernel_Image(3,
	//		data,
	//		1,
	//		true,
	//		"kernel, line test, image",
	//		roadImg);
	//	kernel->runTest();

	//}

	//{

	//	float h_vector[3] = { -1,0,1 }; // horizontal
	//	float v_vector[3] = { 1,2,1 }; // vertical 
	//	Test* kernel = new SeparableKernel_Image(3,
	//		h_vector,
	//		v_vector,
	//		1,
	//		true,
	//		"separable, line test, image",
	//		roadImg);
	//	kernel->runTest();

	//}

	//{

	//	float data[9] = { 0.077847,  0.123317,  0.077847,
	//					  0.123317,  0.195346,  0.123317,
	//		              0.077847,  0.123317,  0.077847 };

	//	Test* kernel = new Kernel_Image(3,
	//		data,
	//		1,
	//		false,
	//		"kernel, Gaussian, image",
	//		imgPath);
	//	kernel->runTest();

	//}

	//{

	//	float h_vector[3] = { 0.27901, 0.44198, 0.27901 }; // horizontal
	//	float v_vector[3] = { 0.27901, 0.44198, 0.27901 }; // vertical 
	//	Test* kernel = new SeparableKernel_Image(3,
	//		h_vector,
	//		v_vector,
	//		1,
	//		false,
	//		"separable, Gaussian, image",
	//		imgPath);
	//	kernel->runTest();

	//}

	//{
	//	float h_vector[3] = { -1,0,1 }; // horizontal
	//	float v_vector[3] = { 1,2,1 }; // vertical 
	//	Test* kernel = new SeparableKernel_Video(3,
	//		h_vector,
	//		v_vector,
	//		1,
	//		false,
	//		1100,
	//		"separable, line test, video",
	//		vidPath);
	//	kernel->runTest();
	//}

	////{
	////	float h_vector[3] = { 0.27901, 0.44198, 0.27901 }; // horizontal
	////	float v_vector[3] = { 0.27901, 0.44198, 0.27901 }; // vertical 

	////	Test* kernel = new SeparableKernel_Video(3,
	////		h_vector,
	////		v_vector,
	////		1,
	////		true,
	////		871,
	////		"separable, Gaussian, video",
	////		vidPath);
	////	kernel->runTest();

	////}
 ////   


	//{

	//	float data[9] = { -1,  -1,  -1,
	//					  -1,   8,  -1,
	//					  -1,  -1,  -1 };
	//	Test* kernel = new Kernel_Video(3,
	//		data,
	//		1,
	//		true,
	//		1100,
	//		"kernel, line test, video",
	//		vidPath);
	//	kernel->runTest();

	//}





    waitKey(0);
    return 0;
}
