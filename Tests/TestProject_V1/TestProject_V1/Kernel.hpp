#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>



class Kernel
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
	
	void initKernel(int* vector_1, int* vector_2, int width)
	{

	}

	// default is 1
	void setDivider(int d)
	{
		divider = d;
	}
	
	void calculateImage(cv::Mat& input, cv::Mat& output)
	{
		if (seperable)
			calculateImageVertex(input, output);
		else
			calculateImageMatrix(input, output);
	}
	
	void printKernel()
	{
		if (seperable)
			printMatrixSeperable();
		else
			printMatrix();
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

			kernel[row][i % width] = values[i];
		}

	}

	void printMatrix()
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

	void printMatrixSeperable()
	{

	}

	void calculateImageMatrix(cv::Mat& input, cv::Mat& output)
	{
		int rows = input.rows - 2;
		int cols = input.cols - 2;
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


				output.at<uchar>(cv::Point(c, r)) = pixelValue / divider;

				pixelValue = 0;
				kr = 0;
				kc = 0;
			}
		}
	}

	void calculateImageVertex(cv::Mat& input, cv::Mat& output)
	{

	}

	int** kernel;
	int width;
	int divider = 1;

	bool seperable;

	int* v_1;  // horizontal
	int* v_2;  // vertical
};

