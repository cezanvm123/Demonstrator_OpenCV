#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>



class Kernel
{
public:

	virtual void initKernel(int* values, int width) = 0;

	// default is 1
	virtual void setDivider(int divider) = 0; 
	virtual void calculateImage(cv::Mat& input, cv::Mat& output) = 0;
	virtual void printKernel() = 0;
};


class Kernel_3X3 : public Kernel  // width is a parameter for now
{
public:
	void initKernel(int* values, int w)
	{
		width = w;

		// setup the 2d array
		kernel = new int* [width];
		for (int i = 0; i < width; i++)
		{ 
			kernel[i] = new int[width];
		}

		fillKernel(values);

	}

	void printKernel()
	{
		for (int r = 0; r < width; r++)
		{
			for (int c = 0; c < width; c++)
			{
				std::cout << kernel[r][c] << " ";

			}
			std::cout << std::endl;
		}
	}

	void setDivider(int d)
	{
		divider = d;
	}


	// special cases calculations 3x3 matrix
	//	- Top left
	//	- Top row 
	//	- Top right

	// - left 
	// - right 

	// - Down left 
	// - Down row
	// - Down right

	// normal calculation




	// temp calculation for now
	// This calculation will shrink the image by: (int)(width/2) *2
	void calculateImage(cv::Mat& input, cv::Mat& output)
	{

		int rows = input.rows - 2;
		int cols = input.cols - 2;
		int pixelValue = 0;
		int intr;	 // internal calculation row
		int intc;    // internal calculation column
		int kr = 0;  // kernel row   
		int kc = 0;  // kernel column

		int shrink = width / 2;    // this is a int so 1.5 will become 1 (expected behaveour)

		for (int r = shrink; r <= rows -shrink ; r++)
		{
			for (int c = shrink; c <= cols - shrink; c++)
			{
				intr = r - shrink;
				intc = c - shrink;

				for (int i = 0; i < pow(width, 2); i++)
				{
					pixelValue += (int)input.at<uchar>(intr + 1, intc + 1) * kernel[kr][kc];

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


				output.at<uchar>(cv::Point(c, r)) = pixelValue/divider;

				pixelValue = 0;
				kr = 0;
				kc = 0;
			}
		}
	}





private:

	void fillKernel(int* values)
	{
		const int totalVals = pow(width, 2);

		int row = -1;
		for (int i = 0; i < totalVals; i++)
		{
			if (i % width == 0)
				row++;

			kernel[row][i%width] = values[i];
		}

		
	}



	int **kernel;
	int width;
	int divider = 1;
};