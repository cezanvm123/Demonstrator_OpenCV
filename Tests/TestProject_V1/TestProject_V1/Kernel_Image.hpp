#pragma once
#include "Test.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Kernel_Image : public Test
{
public: 
	Kernel_Image(int width, float*data, int divider, bool displayImg, string testName, string path) :
		width(width), divider(divider), displayImg(displayImg), Test(testName,path, 1)
	{
		fillKernel(data); // convert 1d data to a 2d matrix
	}

	void runTest()
	{
		readImage();
		if (displayImg)
		{

			cv::namedWindow(getTestName() + " original grey", cv::WINDOW_AUTOSIZE);
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

		int shrink = width / 2;    // this is a int so 1.5 will become 1 (expected behaveour)


		for (int r = shrink; r <= rows - shrink; r++)
		{
			for (int c = shrink; c <= cols - shrink; c++)
			{
				intr = r - shrink;
				intc = c - shrink;

				for (int i = 0; i < pow(width, 2); i++)
				{
					pixelValue += (int)image.at<uchar>(intr + 1, intc + 1) * kernel[kr][kc];

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
		imshow(getTestName() + " processed", img);
	}
	
	
	cv::Mat image; // grayscale

	float** kernel;
	int width;
	int divider;

	bool displayImg;
};