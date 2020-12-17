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
		calculateOutput();
		printResult();
	}

private:

	void readImage() // using path from Test.hpp
	{
		cv::Mat original = cv::imread(getPath(), cv::IMREAD_COLOR);

		// conversion to grayscale image
		cvtColor(original, image, cv::COLOR_BGR2GRAY);

		if (displayImg)
		{
			cv::namedWindow(getTestName() + " original", cv::WINDOW_AUTOSIZE);
			cv::imshow(getTestName() + " original", image);
		}
	}


	void calculateOutput()
	{
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

		timingStart();

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

				output.at<uchar>(cv::Point(c, r)) = pixelValue / divider;

				pixelValue = 0;
			}
		}
		timingStop();

		if (displayImg)
		{
			displayImage(output);
		}
	}


	void displayImage(cv::Mat& img)
	{
		cv::namedWindow(getTestName() + " processed", cv::WINDOW_AUTOSIZE);
		imshow(getTestName() + " processed", img);
	}

	cv::Mat image; // grayscale

	int vectorSize;
	float* h_vector;  //horizontal vector
	float* v_vector;  //vertical vector
	int divider;

	bool displayImg;

};