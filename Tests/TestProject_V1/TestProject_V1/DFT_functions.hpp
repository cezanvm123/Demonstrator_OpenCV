#pragma once
#include <string>
#include <opencv2/core/base.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


namespace DFT_func
{

	void applyFilter(cv::Mat& dft, cv::Mat &filter)
	{
		if (DEBUG)
			imshow("filter", filter);


		cv::Mat splitList[2] = { cv::Mat::zeros(dft.size(), CV_32F),cv::Mat::zeros(dft.size(), CV_32F) };
		split(dft, splitList);

		cv::Mat destList[2] = { cv::Mat::zeros(dft.size(), CV_32F),cv::Mat::zeros(dft.size(), CV_32F) };

		splitList[0].copyTo(destList[0], filter);
		splitList[1].copyTo(destList[1], filter);

		merge(destList, 2, dft);

	}

	static void loadFilter(std::string filterpth, cv::Mat& filter)
	{
		filter = cv::imread(filterpth, cv::IMREAD_GRAYSCALE);
	}


	static void loadImage(std::string path, cv::Mat& img)
	{
		cv::Mat original = cv::imread(path, cv::IMREAD_COLOR);

	}

	static void convertToGrey(cv::Mat& img, cv::Mat& out)
	{
		cvtColor(img, out, cv::COLOR_BGR2GRAY);
	}

	static void getDFT(cv::Mat& input, cv::Mat& output)
	{
		cv::Mat imageFloat;

		//convert from 0 - 255 to 0 - 1 needed for dft function
		input.convertTo(imageFloat, CV_32FC1, 1.0 / 255.0);

		// create Mat object array the first value holds the real data and the second the img data
		// the complex Mat object is filled with 0's 
		cv::Mat imageComplex[2] = { imageFloat, cv::Mat::zeros(input.size(), CV_32F) };

		// this Mat object will contain the real and the imaginary values. 
		cv::Mat combined;
		merge(imageComplex, 2, combined);



		dft(combined, output, cv::DFT_COMPLEX_OUTPUT);
	}


	static void invertDFT(cv::Mat& dftSource, cv::Mat& img)
	{

		// flags
		// - DFT_INVERSE:		This lets the dft function know that we want the inverse and thus passing a complex Mat
		// - DFT_REAL_OUTPUT:	This lets the dft function know we only want real values(as we cannot display complex numbers).
		// - DFT_SCALE			Makes sure the values are normalized
		dft(dftSource, img, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
	}


	// recenterDFT but in reverse
	static void de_recenterDFT(cv::Mat& dftSource)
	{
		int centerX = dftSource.cols / 2;
		int centerY = dftSource.rows / 2;


		cv::Mat c1(dftSource, cv::Rect(0, 0, centerX, centerY));
		cv::Mat c2(dftSource, cv::Rect(centerX, 0, centerX, centerY));

		cv::Mat c3(dftSource, cv::Rect(0, centerY, centerX, centerY));
		cv::Mat c4(dftSource, cv::Rect(centerX, centerY, centerX, centerY));


		cv::Mat temp;
		c4.copyTo(temp);
		c1.copyTo(c4);
		temp.copyTo(c1);

		c3.copyTo(temp);
		c2.copyTo(c3);
		temp.copyTo(c2);
	}

	// receneter the dft sow the low freq is in the middle and high freq at the corners
	static void recenterDFT(cv::Mat& dftSource)
	{
		int centerX = dftSource.cols / 2;
		int centerY = dftSource.rows / 2;


		cv::Mat c1(dftSource, cv::Rect(0, 0, centerX, centerY));
		cv::Mat c2(dftSource, cv::Rect(centerX, 0, centerX, centerY));

		cv::Mat c3(dftSource, cv::Rect(0, centerY, centerX, centerY));
		cv::Mat c4(dftSource, cv::Rect(centerX, centerY, centerX, centerY));


		cv::Mat temp;
		c1.copyTo(temp);
		c4.copyTo(c1);  //corner4 is now overwritten with data from corner1
		temp.copyTo(c4); // corner1's data stored in the temp var is now written to corner4

		c2.copyTo(temp);
		c3.copyTo(c2);  //corner4 is now overwritten with data from corner1
		temp.copyTo(c3); // corner1's data stored in the temp var is now written to corner4

	}

	// this function is used for visualizing only the dft cannot be used for image processing after the normilization.
	// reference is not used here to make sure the original is not altered.
	static void visualizeDFT(cv::Mat dftSource, std::string name)
	{
		cv::Mat splitList[2] = { cv::Mat::zeros(dftSource.size(), CV_32F),cv::Mat::zeros(dftSource.size(), CV_32F) };

		split(dftSource, splitList);

		// will hold the dft magnitudes for better visualization. 
		cv::Mat dftMag;

		magnitude(splitList[0], splitList[1], dftMag);

		// adds a 1 to all the magnitudes to make sure the following part won't fail. 
		dftMag += cv::Scalar::all(1);

		// cannot take the log of 0
		log(dftMag, dftMag);

		// further normilazing the values to be between 0 - 1
		normalize(dftMag, dftMag, 0, 1, cv::NORM_MINMAX);

		cv::imshow(name, dftMag);
		cv::waitKey(1);
	}

}

