#pragma once
#include <opencv2/core/base.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>       /* exp */




// https://hicraigchen.medium.com/digital-image-processing-using-fourier-transform-in-python-bcb49424fd82 for masks

using namespace cv;

class MaskGenerator
{
public:

	//static Mat getGuasian(int x, int y)
	//{
	//	 cv::Mat mask = cv::Mat::zeros(cv::Size(1, 49), CV_8UC1);


	//	return mask;
	//}

	static Mat getPerfectHighPass(int x, int y, int size)
	{
		cv::Mat mask = cv::Mat(cv::Size(x,y), CV_8UC1, Scalar(255, 255, 255));

		cv::circle(mask, cv::Point(mask.rows / 2, mask.cols / 2), x / size, cv::Scalar(0, 0, 0), -1, 8, 0);

		return mask;
	}

	static Mat getPerfectLowPass(int x, int y, int size)
	{
		cv::Mat mask = cv::Mat::zeros(cv::Size(x,y), CV_8UC1);

		cv::circle(mask, cv::Point(mask.rows / 2, mask.cols / 2), x/size, cv::Scalar(255, 0, 0), -1, 8, 0);

		return mask;
	}
	
	static float distance(int x, int y, int xc, int xy)
	{
		return sqrt(powf(x - xc, 2) + powf(y - xy, 2));
	}

	static Mat getButterworthLowPass(int x, int y, int n, int D0)
	{
		cv::Mat mask = cv::Mat::zeros(cv::Size(x, y), CV_8UC1);

		for (int c = 0; c < x; c++)
		{
			for (int r = 0; r < y; r++)
			{
				float D = distance(c, r, x / 2, y / 2); // Euclidean Distance

				float value = 1 / (1 + powf((D / D0), (2 * n))) *255;

				if (value < 1)
					value = 0;
				if (value > 255)
					value = 255;

				//cout << value << endl;
				mask.at<uchar>(cv::Point(r, c)) = value;
			}
		}
		//imshow("getButterworth_LP", mask);
		waitKey(1);
		return mask;
	}



	static Mat getButterworthHighPass(int x, int y, int n, int D0)
	{
		cv::Mat mask = cv::Mat::zeros(cv::Size(x, y), CV_8UC1);

		for (int c = 0; c < x; c++)
		{
			for (int r = 0; r < y; r++)
			{
				float D = distance(c, r, x / 2, y / 2);  // Euclidean Distance

				float value = 1 / (1 + powf((D0 / D), (2 * n))) *255;

				if (value < 1)
					value = 0;
				if (value > 255)
					value = 255;
				

			//	std::cout << c << " " << r << std::endl;
				mask.at<uchar>(cv::Point(r, c)) = value;
			}
		}
		//imshow("getButterworth_HP", mask);
		waitKey(1);
		return mask;
	}

	static Mat getButterworthBandPass(int x, int y, int innerN, int innerD0, int outerN, int outerD0 )
	{
		cv::Mat mask = cv::Mat::zeros(cv::Size(x, y), CV_8UC1);

		for (int c = 0; c < x; c++)
		{
			for (int r = 0; r < y; r++)
			{
				float D = distance(c, r, x / 2, y / 2);  // Euclidean Distance

				float innerValue = 1 / (1 + powf((outerD0 / D), (2 * outerN))) * 255; //highpass
				float outerValue = 1 / (1 + powf((D / innerD0), (2 * innerN))) * 255; //lowpass

				float value = 0;
				if (innerValue > outerValue)
					value = innerValue;
				else
					value = outerValue;

				if (value < 1)
					value = 0;
				if (value > 255)
					value = 255;


				//	std::cout << c << " " << r << std::endl;
				mask.at<uchar>(cv::Point(r, c)) = value;
			}
		}
		//imshow("getButterworth_BP", mask);
		waitKey(1);
		return mask;
	}



	static Mat getGuassianLowPass(int x, int y, int D0)
	{
		cv::Mat mask = cv::Mat::zeros(cv::Size(x, y), CV_8UC1);

		for (int c = 0; c < x; c++)
		{
			for (int r = 0; r < y; r++)
			{
				float D = distance(r, c, x / 2, y / 2); // Euclidean Distance
				float ex1 = pow(D, 2);
				float ex2 = 2 * pow(D0, 2);


				float value = exp(ex1/ex2);

				if (value < 1)
					value = 0;
				if (value > 255)
					value = 255;
			
			//	value = value /255;
				
				mask.at<uchar>(cv::Point(r, c)) = value;
			}
		}
		//imshow("Gaussian", mask);
		waitKey(1);
		return mask;
	}
};
