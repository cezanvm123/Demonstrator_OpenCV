#pragma once
// https://docs.opencv.org/3.4/d8/d01/tutorial_discrete_fourier_transform.html

#define DEBUG true

#include "Test.hpp"


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class DFT : public Test
{

public:


	DFT(bool displayImg, string filter, string testName, string path) :
		displayImg(displayImg), filterPath(filter), Test(testName, path, 1)
	{
		loadFilter();
	}


	DFT(bool displayImg, Mat filter, string testName, string path) :
		displayImg(displayImg), filter(filter), Test(testName, path, 1)
	{ }


	void runTest()
	{

	/*	MaskGenerator::getPerfectHighPass(240, 240, 10);
		MaskGenerator::getPerfectLowPass(240, 240, 10);*/


		//MaskGenerator::getButterworthLowPass(240, 240, 5, 20);

		loadImage();
		if(displayImg)
			imshow ("original", image);

		Mat dft; 
		getDFT(image, dft);
		if(DEBUG)
			visualizeDFT(dft, "non centered");


		recenterDFT(dft);
		if(DEBUG)
			visualizeDFT(dft, "Centered");


		// apply filter
		applyFilter(dft);
		if (DEBUG)
			visualizeDFT(dft, "After filter");


		de_recenterDFT(dft);
		if(DEBUG)
			visualizeDFT(dft, "de-reCentered?");

		Mat result; 
		invertDFT(dft, result);
		if(displayImg)
			imshow("result", result);




	}


private:


	void applyFilter(Mat& dft)
	{
		if (DEBUG)
			imshow("filter", filter);


		Mat splitList[2] = { Mat::zeros(dft.size(), CV_32F),Mat::zeros(dft.size(), CV_32F) };
		split(dft, splitList);

		Mat destList[2] = { Mat::zeros(dft.size(), CV_32F),Mat::zeros(dft.size(), CV_32F) };

		splitList[0].copyTo(destList[0], filter);
		splitList[1].copyTo(destList[1], filter);

		merge(destList, 2, dft);
		
	}

	void loadFilter()
	{
		filter = cv::imread(filterPath, cv::IMREAD_GRAYSCALE);
	}

	void loadImage()
	{
		cv::Mat original = cv::imread(getPath(), cv::IMREAD_COLOR);
		
		timingStop();

		// conversion to grayscale image
		timingStart(MeasurementType::IMAGE_CONVERTION);
		cvtColor(original, image, cv::COLOR_BGR2GRAY);
	}


	void getDFT(Mat& input, Mat& output)
	{
		Mat imageFloat;

		//convert from 0 - 255 to 0 - 1 needed for dft function
		input.convertTo(imageFloat, CV_32FC1, 1.0 / 255.0);

		// create Mat object array the first value holds the real data and the second the img data
		// the complex Mat object is filled with 0's 
		Mat imageComplex[2] = { imageFloat, Mat::zeros(input.size(), CV_32F) };

		// this Mat object will contain the real and the imaginary values. 
		Mat combined;
		merge(imageComplex, 2, combined);


		
		dft(combined, output, DFT_COMPLEX_OUTPUT);
	}



	void invertDFT(Mat& dftSource, Mat& img)
	{

		// flags
		// - DFT_INVERSE:		This lets the dft function know that we want the inverse and thus passing a complex Mat
		// - DFT_REAL_OUTPUT:	This lets the dft function know we only want real values(as we cannot display complex numbers).
		// - DFT_SCALE			Makes sure the values are normalized
		dft(dftSource, img, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
	}

	// recenterDFT but in reverse
	void de_recenterDFT(Mat& dftSource)
	{
		int centerX = dftSource.cols / 2;
		int centerY = dftSource.rows / 2;


		Mat c1(dftSource, Rect(0, 0, centerX, centerY));
		Mat c2(dftSource, Rect(centerX, 0, centerX, centerY));

		Mat c3(dftSource, Rect(0, centerY, centerX, centerY));
		Mat c4(dftSource, Rect(centerX, centerY, centerX, centerY));


		Mat temp;
		c4.copyTo(temp);
		c1.copyTo(c4);  
		temp.copyTo(c1); 

		c3.copyTo(temp);
		c2.copyTo(c3);  
		temp.copyTo(c2); 
	}


	// receneter the dft sow the low freq is in the middle and high freq at the corners
	void recenterDFT(Mat& dftSource)
	{
		int centerX = dftSource.cols / 2;
		int centerY = dftSource.rows / 2;

		
		Mat c1(dftSource, Rect(0, 0, centerX, centerY));
		Mat c2(dftSource, Rect(centerX, 0, centerX, centerY));

		Mat c3(dftSource, Rect(0, centerY, centerX, centerY));
		Mat c4(dftSource, Rect(centerX, centerY, centerX, centerY));


		Mat temp; 
		c1.copyTo(temp);
		c4.copyTo(c1);  //corner4 is now overwritten with data from corner1
		temp.copyTo(c4); // corner1's data stored in the temp var is now written to corner4

		c2.copyTo(temp);
		c3.copyTo(c2);  //corner4 is now overwritten with data from corner1
		temp.copyTo(c3); // corner1's data stored in the temp var is now written to corner4

	}

	// this function is used for visualizing only the dft cannot be used for image processing after the normilization.
	// reference is not used here to make sure the original is not altered.
	void visualizeDFT(Mat dftSource, string name )
	{
		Mat splitList[2] = { Mat::zeros(dftSource.size(), CV_32F),Mat::zeros(dftSource.size(), CV_32F) };

		split(dftSource, splitList);

		// will hold the dft magnitudes for better visualization. 
		Mat dftMag;

		magnitude(splitList[0], splitList[1], dftMag);

		// adds a 1 to all the magnitudes to make sure the following part won't fail. 
		dftMag += Scalar::all(1);

		// cannot take the log of 0
		log(dftMag, dftMag);

		// further normilazing the values to be between 0 - 1
		normalize(dftMag, dftMag, 0, 1, NORM_MINMAX);

		imshow(name, dftMag);
		waitKey(1);
	}


	string filterPath;

	bool displayImg;

	cv::Mat image;
	cv::Mat filter;


};