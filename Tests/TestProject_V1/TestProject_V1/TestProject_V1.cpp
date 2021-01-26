// TestProject_V1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Opencv C++ Example of Operation on Arrays:absdiff  
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>


#include "Test.hpp"

#include "DFT.hpp"
#include "DFT_Video.hpp"
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

    String roadImg = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\road.png";

	String imgPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\openCV_240.png";
	String vidPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\OpenCV.mp4";
	
	string dftFilterPath = "D:\\School\\Signals\\Demonstrator_OpenCV\\Tests\\TestProject_V1\\TestProject_V1\\TestImages\\Masks\\Mask1_lowpass.png";
	

	bool displays = false;  // to be set to true in second run

	std::cout << "Running..." << std::endl;
	
	
	/*
		   ______                      _
		  / ____/___ ___  ____________(_)___ _____
		 / / __/ __ `/ / / / ___/ ___/ / __ `/ __ \
		/ /_/ / /_/ / /_/ (__  |__  ) / /_/ / / / /
		\____/\__,_/\__,_/____/____/_/\__,_/_/ /_/

	*/
	{
		float data[9] = { 0.077847,	0.123317,	0.077847,
						  0.123317,	0.195346,	0.123317,
						  0.077847,	0.123317,	0.077847 };
		Test* kernel = new Kernel_Video(3,
			data,
			1,
			displays,
			1100,
			"kernel, Gaussian Blur, video",
			vidPath);
		kernel->runTest();


		float h_vector[3] = { 0.27901,0.44198,0.27901 }; // horizontal
		float v_vector[3] = { 1,2,1 }; // vertical 
		Test* sepKernel = new SeparableKernel_Video(3,
			h_vector,
			v_vector,
			1,
			displays,
			1100,
			"separable, Gaussian Blur, video",
			vidPath);
		sepKernel->runTest();


	}

	/*
		   _____ __                                _
		  / ___// /_  ____ __________  ___  ____  (_)___  ____ _
		  \__ \/ __ \/ __ `/ ___/ __ \/ _ \/ __ \/ / __ \/ __ `/
		 ___/ / / / / /_/ / /  / /_/ /  __/ / / / / / / / /_/ /
		/____/_/ /_/\__,_/_/  / .___/\___/_/ /_/_/_/ /_/\__, /
							 /_/                       /____/
	*/
	{
		float data[9] = { 0,  -1,  0,
						  -1,  5,  -1,
						  0,  -1,  0 };
		Test* kernel = new Kernel_Video(3,
			data,
			1,
			displays,
			1100,
			"kernel, Sharpening test, video",
			vidPath);
		kernel->runTest();


		float h_vector[3] = { -1, 1, -1 }; // horizontal
		float v_vector[3] = { 1, 9, 1 }; // vertical 
		Test* sepKernel = new SeparableKernel_Video(3,
			h_vector,
			v_vector,
			1,
			displays,
			1100,
			"separable, Sharpening test, video",
			vidPath);
		sepKernel->runTest();


	}

	/*
			______    __                  __     __            __  _
		   / ____/___/ /___ ____     ____/ /__  / /____  _____/ /_(_)___  ____
		  / __/ / __  / __ `/ _ \   / __  / _ \/ __/ _ \/ ___/ __/ / __ \/ __ \
		 / /___/ /_/ / /_/ /  __/  / /_/ /  __/ /_/  __/ /__/ /_/ / /_/ / / / /
		/_____/\__,_/\__, /\___/   \__,_/\___/\__/\___/\___/\__/_/\____/_/ /_/
					/____/
	*/
	{

		float data[9] = { -1,  -1,  -1,
						  -1,   8,  -1,
						  -1,  -1,  -1 };
		Test* kernel = new Kernel_Video(3,
			data,
			1,
			displays,
			1100,
			"kernel, Gaussian Blur, video",
			vidPath);
		kernel->runTest();


		float h_vector[3] = { -1,0,1 }; // horizontal
		float v_vector[3] = { 1,2,1 }; // vertical 
		Test* sepKernel = new SeparableKernel_Video(3,
			h_vector,
			v_vector,
			1,
			displays,
			1100,
			"separable, Gaussian Blur, video",
			vidPath);
		sepKernel->runTest();

	}

	/*
			__
		   / /   ____ _      __      ____  ____ ___________
		  / /   / __ \ | /| / /_____/ __ \/ __ `/ ___/ ___/
		 / /___/ /_/ / |/ |/ /_____/ /_/ / /_/ (__  |__  )
		/_____/\____/|__/|__/     / .___/\__,_/____/____/
								 /_/
	*/
	{
		Test* dftTest = new DFT_Video(displays, MaskGenerator::getButterworthLowPass(240, 240, 5, 25), "DFT_LP test", vidPath, 1100);
		dftTest->runTest();
	}


	/* 
			__  ___       __
		   / / / (_)___ _/ /_        ____  ____ ___________
		  / /_/ / / __ `/ __ \______/ __ \/ __ `/ ___/ ___/
		 / __  / / /_/ / / / /_____/ /_/ / /_/ (__  |__  )
		/_/ /_/_/\__, /_/ /_/     / .___/\__,_/____/____/
				/____/           /_/
	*/
	{
		Test* dftTest = new DFT_Video(displays, MaskGenerator::getButterworthHighPass(240, 240, 5, 25), "DFT_HP test", vidPath, 1100);
		dftTest->runTest();
	}

	/*
			____                  __
		   / __ )____ _____  ____/ /     ____  ____ ___________
		  / __  / __ `/ __ \/ __  /_____/ __ \/ __ `/ ___/ ___/
		 / /_/ / /_/ / / / / /_/ /_____/ /_/ / /_/ (__  |__  )
		/_____/\__,_/_/ /_/\__,_/     / .___/\__,_/____/____/
									 /_/
	*/
	{
		Test* dftTest = new DFT_Video(displays, MaskGenerator::getButterworthBandPass(240, 240, 5, 25, 10, 125), "DFT_BP test", vidPath, 1100);
		dftTest->runTest();
	}
	

    return 0;
}
