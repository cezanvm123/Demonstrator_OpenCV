#pragma once

#include "DFT.hpp"



#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



class DFT_Video : public Test
{
public:
	
	DFT_Video(bool displayImg, string filter, string testName, string path, int frames) :
		displayImg(displayImg), filterPath(filter), Test(testName, path, frames)
	{
		
	}

	DFT_Video(bool displayImg, Mat filter, string testName, string path, int frames) :
		displayImg(displayImg), filter(filter), Test(testName, path, frames)
	{ }

	void runTest()
	{
		
	}


private:


	string filterPath;

	bool displayImg;

	cv::Mat image;
	cv::Mat filter;
};
