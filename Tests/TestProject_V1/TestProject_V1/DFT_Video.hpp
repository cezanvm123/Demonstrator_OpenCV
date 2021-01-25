#pragma once

#include "DFT.hpp"



#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



class DFT_Video : public Test
{
public:
	
	DFT_Video(bool displayImg, string filterpth, string testName, string path, int frames) :
		displayImg(displayImg), filterPath(filterpth), Test(testName, path, frames)
	{
		DFT_func::loadFilter(filterPath, filter);
	}

	DFT_Video(bool displayImg, Mat filter, string testName, string path, int frames) :
		displayImg(displayImg), filter(filter), Test(testName, path, frames)
	{ }

	void runTest()
	{
		readVideo();
		while (true)
		{
			// start IMAGE_LOAD time here
			timingStart(MeasurementType::IMAGE_LOAD);
			if (!video.read(original)) // the video has no frames left
				break;
			timingStop();

			timingStart(MeasurementType::IMAGE_CONVERTION);
			DFT_func::convertToGrey(original, image);
			timingStop();

			if (displayImg)
				imshow("original", image);

			timingStart(MeasurementType::KERNEL_CALCULATION);
			Mat dft;
			DFT_func::getDFT(image, dft);
			if (DEBUG)
				DFT_func::visualizeDFT(dft, "non centered");


			DFT_func::recenterDFT(dft);
			if (DEBUG)
				DFT_func::visualizeDFT(dft, "Centered");


			// apply filter
			DFT_func::applyFilter(dft, filter);
			if (DEBUG)
				DFT_func::visualizeDFT(dft, "After filter");


			DFT_func::de_recenterDFT(dft);
			if (DEBUG)
				DFT_func::visualizeDFT(dft, "de-reCentered?");

			Mat result;
			DFT_func::invertDFT(dft, result);
			timingStop();

			timingStart(MeasurementType::IMAGE_DISPLAY);
			if (displayImg)
			{
				imshow("result", result);
				waitKey(1);
			}
			timingStop();

			printResult();
				
		}
	}

	void readVideo()
	{
		video = cv::VideoCapture(getPath(), cv::CAP_ANY);
		if (!video.isOpened()) {
			std::cout << "ERROR! Unable to open video\n";
			throw;
		}
	}


private:

	cv::VideoCapture  video;

	string filterPath;

	bool displayImg;

	cv::Mat original;
	cv::Mat image;
	cv::Mat filter;
};
