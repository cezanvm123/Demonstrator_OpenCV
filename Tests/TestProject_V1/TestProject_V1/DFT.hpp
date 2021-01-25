#pragma once
// https://docs.opencv.org/3.4/d8/d01/tutorial_discrete_fourier_transform.html

#define DEBUG false

#include "Test.hpp"
#include "DFT_functions.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;

class DFT : public Test
{

public:

	friend class DFT_video;

	DFT(bool displayImg, string filterpth, string testName, string path) :
		displayImg(displayImg), filterPath(filterpth), Test(testName, path, 1)
	{
		DFT_func::loadFilter(filterPath, filter);
	}


	DFT(bool displayImg, Mat filter, string testName, string path) :
		displayImg(displayImg), filter(filter), Test(testName, path, 1)
	{ }


	// see DFT_functions.hpp for an explanation about the DFT functions
	void runTest()
	{

		timingStart(MeasurementType::IMAGE_LOAD);
		DFT_func::loadImage(getPath() , image);
		timingStop();

		timingStart(MeasurementType::IMAGE_CONVERTION);
		DFT_func::convertToGrey(image, image);
		timingStop();

		if(displayImg)
			imshow ("original", image);

		Mat dft; 
		DFT_func::getDFT(image, dft);
		if(DEBUG)
			DFT_func::visualizeDFT(dft, "non centered");


		DFT_func::recenterDFT(dft);
		if(DEBUG)
			DFT_func::visualizeDFT(dft, "Centered");


		// apply filter
		DFT_func::applyFilter(dft, filter);
		if (DEBUG)
			DFT_func::visualizeDFT(dft, "After filter");


		DFT_func::de_recenterDFT(dft);
		if(DEBUG)
			DFT_func::visualizeDFT(dft, "de-reCentered?");

		Mat result; 
		DFT_func::invertDFT(dft, result);
		if(displayImg)
			imshow("result", result);


		printResult();

	}


private:

	string filterPath;
	bool displayImg;

	cv::Mat image;
	cv::Mat filter;


};