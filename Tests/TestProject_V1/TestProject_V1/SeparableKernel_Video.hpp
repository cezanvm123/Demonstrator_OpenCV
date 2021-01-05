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

		if (displayImg)
		{
			cv::namedWindow(getTestName() + " original", cv::WINDOW_AUTOSIZE);
			cv::namedWindow(getTestName() + " processed", cv::WINDOW_AUTOSIZE);
		}
		calculateOutput();
		
		printResult();
	}

private:

	void readVideo() // using path from Test.hpp
	{
		video = cv::VideoCapture(getPath(), cv::CAP_ANY);
		if (!video.isOpened()) {
			std::cout << "ERROR! Unable to open video\n";
			throw;
		}
	}

	void calculateOutput()
	{
		
		while (true)
		{
			// start IMAGE_LOAD time here
			timingStart(MeasurementType::IMAGE_LOAD);
			if (!video.read(currentFrameColor)) // the video has no frames left
				break; 
			timingStop();



			
			// start IMAGE_CONVERTION time here
			timingStart(MeasurementType::IMAGE_CONVERTION);
			cvtColor(currentFrameColor, currentFrameGrey, cv::COLOR_BGR2GRAY);
			timingStop();



			// start KERNEL_CALCULATION time here
			timingStart(MeasurementType::KERNEL_CALCULATION);
			cv::Mat output(cv::Size(currentFrameGrey.cols, currentFrameGrey.rows), CV_8UC1);
			int rows = currentFrameGrey.rows - 2;
			int cols = currentFrameGrey.cols - 2;
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
						vec[i] = (currentFrameGrey.at<uchar>(r + (i - 1), c - 1) * h_vector[0]) + (currentFrameGrey.at<uchar>(r + (i - 1), c) * h_vector[1]) + (currentFrameGrey.at<uchar>(r + (i - 1), c + 1) * h_vector[2]);
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


			// start IMAGE_DISPLAY time here
			timingStart(MeasurementType::IMAGE_DISPLAY);
			if (displayImg)
			{
				displayFrame(output);
			}
			timingStop();


		}
	}

	void displayFrame(cv::Mat& img)
	{
		
		//cv::imshow(getTestName() + " original", currentFrameColor);

		
		imshow(getTestName() + " processed", img);

		cv::waitKey(1);
	}

	cv::VideoCapture  video;
	
	cv::Mat currentFrameColor; // current color
	cv::Mat currentFrameGrey; // current grayscale

	int vectorSize;
	float* h_vector;  //horizontal vector
	float* v_vector;  //vertical vector
	int divider;

	bool displayImg;
};