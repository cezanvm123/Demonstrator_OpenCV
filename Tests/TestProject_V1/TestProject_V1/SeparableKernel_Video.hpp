#pragma once
#include "Test.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

class SeparableKernel_Video : public Test
{
public:
	SeparableKernel_Video(int vectorSize, float* h_vector, float* v_vector, int divider, bool displayImg, int frameCount, string testName, string path) :
		vectorSize(vectorSize), h_vector(h_vector), v_vector(v_vector), divider(divider), displayImg(displayImg), Test(testName, path, frameCount)
	{}

	void runTest()
	{
		readVideo();
		calculateOutput();
		printResult();
	}

private:

	void readVideo() // using path from Test.hpp
	{
		video = cv::VideoCapture(getPath(), cv::CAP_ANY);
		if (!video.isOpened()) {
			std::cout << "ERROR! Unable to open camera\n";
			throw;
		}
	}

	void calculateOutput()
	{
		
		while (video.read(original))
		{
			cvtColor(original, image, cv::COLOR_BGR2GRAY);
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
	}

	void displayImage(cv::Mat& img)
	{
		cv::namedWindow(getTestName() + " original", cv::WINDOW_AUTOSIZE);
		cv::imshow(getTestName() + " original", original);

		cv::namedWindow(getTestName() + " processed", cv::WINDOW_AUTOSIZE);
		imshow(getTestName() + " processed", img);

		cv::waitKey(1);
	}

	cv::VideoCapture  video;
	
	cv::Mat original; // current color
	cv::Mat image; // current grayscale

	int vectorSize;
	float* h_vector;  //horizontal vector
	float* v_vector;  //vertical vector
	int divider;

	bool displayImg;
};