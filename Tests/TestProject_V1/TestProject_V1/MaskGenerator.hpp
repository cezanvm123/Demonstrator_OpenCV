#pragma once
#include <opencv2/core/base.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



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


	//static Mat getButterworthLowPass(int x, int y, int n, int D0)
	//{
	//	cv::Mat mask = cv::Mat::zeros(cv::Size(x, y), CV_8UC1);

	//	

	//	for (int c = 0; c < x; c++)
	//	{
	//		for (int r = 0; r < y; r++)
	//		{
	//			float D = sqrt(pow(r, 2) + pow(c, 2));   // Euclidean Distance

	//			mask.at<uchar>(cv::Point(r, c)) = 1 / 1 + powf((D/D0),(2*n));
	//		}
	//	}
	//	imshow("getButterworth_LP", mask);
	//	waitKey(1);
	//	return mask;
	//}


	//static Mat getButterworthHighPass(int x, int y, int n, int D0)
	//{
	//	cv::Mat mask = cv::Mat::zeros(cv::Size(x, y), CV_8UC1);



	//	for (int c = 0; c < x; c++)
	//	{
	//		for (int r = 0; r < y; r++)
	//		{
	//			float D = sqrt(pow(r, 2) + pow(c, 2));   // Euclidean Distance

	//			mask.at<uchar>(cv::Point(r, c)) = 1 / 1 + powf((D0 / D), (2 * n));

	//			std::cout << c << " " << r << std::endl;
	//		}
	//	}
	//	imshow("getButterworth_HP", mask);
	//	waitKey(1);
	//	return mask;
	//}
};
