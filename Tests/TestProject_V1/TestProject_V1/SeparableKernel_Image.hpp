#pragma once
#include "Test.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class SeparableKernel_Image : public Test
{
public:
	SeparableKernel_Image(int vectorSize, float* h_vector, float* v_vector, int divider, bool displayImg, string testName, string path) :
		vectorSize(vectorSize), h_vector(h_vector), v_vector(v_vector), divider(divider), displayImg(displayImg), Test(testName, path, 1)
	{}

	void runTest()
	{
		readImage();

		if (displayImg)
		{
			cv::namedWindow(getTestName() + " original grey ", cv::WINDOW_AUTOSIZE);
			cv::namedWindow(getTestName() + " processed", cv::WINDOW_AUTOSIZE);
		}

		calculateOutput();
		printResult();
	}

private:

	void readImage() // using path from Test.hpp
	{
		timingStart(MeasurementType::IMAGE_LOAD);
		cv::Mat original = cv::imread(getPath(), cv::IMREAD_COLOR);
		timingStop();

		// conversion to grayscale image
		timingStart(MeasurementType::IMAGE_CONVERTION);
		cvtColor(original, image, cv::COLOR_BGR2GRAY);
		timingStop();

	}


	void calculateOutput()
	{
		timingStart(MeasurementType::KERNEL_CALCULATION);
		cv::Mat output(cv::Size(image.cols, image.rows), CV_8UC1);

		int rows = image.rows - 2;
		int cols = image.cols - 2;
		int pixelValue = 0;
		int intr;	 // internal calculation row
		int intc;    // internal calculation column
		int kr = 0;  // kernel row   
		int kc = 0;  // kernel column

		int shrink = vectorSize / 2;    // this is a int so 1.5 will become 1 (expected behaveour)

		int* vec = new int[vectorSize];

		

		for (int r = shrink; r <= rows - shrink; r++)
		{
			for (int c = shrink; c <= cols - shrink; c++)
			{
				for (int i = 0; i < vectorSize; i++)
				{
					vec[i] = (image.at<uchar>(r + (i - 1), c - 1) * h_vector[0]) + (image.at<uchar>(r + (i - 1), c) * h_vector[1]) + (image.at<uchar>(r + (i - 1), c + 1) * h_vector[2]);
				}

				for (int i = 0; i < vectorSize; i++)
				{
					pixelValue += vec[i] * v_vector[i];
				}

				if (pixelValue > 255)
					pixelValue = 255;
				if (pixelValue < 1)
					pixelValue = 0;

				output.at<uchar>(cv::Point(c, r)) = pixelValue / divider;

				pixelValue = 0;
			}
		}
		timingStop();

		timingStart(MeasurementType::IMAGE_DISPLAY);
		if (displayImg)
		{
			displayImage(output);
		}
		timingStop();
	}


	void displayImage(cv::Mat& img)
	{
		cv::imshow(getTestName() + " original grey", image);
		cv::imshow(getTestName() + " processed", img);
	}

	cv::Mat image; // grayscale

	int vectorSize;
	float* h_vector;  //horizontal vector
	float* v_vector;  //vertical vector
	int divider;

	bool displayImg;

};