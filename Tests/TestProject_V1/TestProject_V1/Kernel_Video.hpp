#pragma once
#include <string>
#include "Test.hpp"
#include <opencv2/videoio.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

class Kernel_Video : public Test
{
public:

	Kernel_Video(int width, float* data,  int divider, bool displayVideo, int frameCount, string testName, string path) :
		width(width), divider(divider), displayVideo(displayVideo), Test(testName, path, frameCount)
	{ 
		fillKernel(data); // convert 1d data to a 2d matrix
	}


	void runTest()
	{
		readVideo();

		if (displayVideo)
		{
			cv::namedWindow(getTestName() + " original", cv::WINDOW_AUTOSIZE);
			cv::namedWindow(getTestName() + " processed", cv::WINDOW_AUTOSIZE);
		}
		calculateOutput();
		printResult();
	}


private:

	void fillKernel(float* values)
	{
		kernel = new float* [width]; // mem allocation
		for (int i = 0; i < width; i++)
		{
			kernel[i] = new float[width]; // mem allocation
		}


		const int totalVals = pow(width, 2);

		int row = -1;
		for (int i = 0; i < totalVals; i++)
		{
			if (i % width == 0)
				row++;

			kernel[row][i % width] = values[i];
		}

	}

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

			int shrink = width / 2;    // this is a int so 1.5 will become 1 (expected behaveour)


			for (int r = shrink; r <= rows - shrink; r++)
			{
				for (int c = shrink; c <= cols - shrink; c++)
				{
					intr = r - shrink;
					intc = c - shrink;

					for (int i = 0; i < pow(width, 2); i++)
					{
						pixelValue += (int)currentFrameGrey.at<uchar>(intr + 1, intc + 1) * kernel[kr][kc];

						kc++;
						intc++;
						if (kc == width)
						{
							kc = 0;
							intc = c - shrink;
							kr++;
							intr++;
						}
					}

					if (pixelValue > 255)
						pixelValue = 255;
					if (pixelValue < 1)
						pixelValue = 0;

					output.at<uchar>(cv::Point(c, r)) = pixelValue / divider;

					pixelValue = 0;
					kr = 0;
					kc = 0;
				}
			}
			timingStop();

			// start IMAGE_DISPLAY time here
			timingStart(MeasurementType::IMAGE_DISPLAY);
			if (displayVideo)
			{
				displayFrame(output);
			}
			timingStop();
		}
	}



	void displayFrame(cv::Mat& img)
	{

		cv::imshow(getTestName() + " original", currentFrameColor);


		imshow(getTestName() + " processed", img);

		cv::waitKey(1);
	}


	cv::VideoCapture  video;

	cv::Mat currentFrameColor; // current color
	cv::Mat currentFrameGrey; // current grayscale

	float** kernel;
	int width;
	int divider;

	bool displayVideo;
};