#pragma once
#include <string>
#include <opencv2/core/base.hpp>
#include "DataExporter.hpp"



#define FRAME_COUNT 50

/* 
	Image load is in the case of a video test the time video.read(img) function takes.
*/
enum MeasurementType { IMAGE_LOAD, IMAGE_CONVERTION, KERNEL_CALCULATION, IMAGE_DISPLAY };

using namespace std;

class Test
{
public: 
	Test(string testName, string path, int frameCount) : 
		testName(testName), path(path), frameCount(frameCount) 
	{
		frameTime = new long[frameCount];
		testData = new Data[frameCount];
	};
	virtual void runTest() = 0;

	void printResult()
	{
		DataExporter::writeData(testData, dataIndex, testName);
		//std::cout << "*******************" << testName << "*******************" << std::endl;
		//std::cout << "Amount of frames processed: " << dataIndex << std::endl;


		//long totalNS = 0;
		//for (int i = 0; i < dataIndex; i++)
		//{
		//	totalNS += frameTime[i];
		//}

		//std::cout << "Total processing time: " << (float)totalNS / 1000000.0 << "s" << std::endl;   // 1000000.0 is based on a nanosecond to second conversion taking into account the 1000 divided already
		//float avgFrameTime = (float)totalNS / (float)dataIndex;
		//std::cout << "Average frame time: " << avgFrameTime / 1000 << "ms" << std::endl;   // same here


		//float avgFPS = 1000000.0 / avgFrameTime;

		//std::cout << "Average fps: " << avgFPS << "fps" << std::endl;
		//std::cout << "-----------------------------------------------------------------" << std::endl << std::endl << std::endl;


	}

	string getPath()
	{
		return path;
	}

	string getTestName()
	{
		return testName;
	}

	void timingStart(MeasurementType type)
	{
		currentType = type;
		start = std::chrono::steady_clock::now();
		
	}

	void timingStop()
	{
		end = std::chrono::steady_clock::now();

		chrono::nanoseconds time = end - start;

		//frameTime[dataIndex] = time.count() / 1000; // divided by 1000 as the numbers got to big

		switch (currentType)
		{
		case MeasurementType::IMAGE_LOAD:  // this is the first timing so the currentDataObject is created here
			currentDataObject = new Data();
			currentDataObject->imageLoadTime = time.count();
			break;

		case MeasurementType::IMAGE_CONVERTION:
			currentDataObject->imageConvertionTime = time.count();
			break;

		case MeasurementType::KERNEL_CALCULATION:
			currentDataObject->kernelCalculationTime = time.count();
			break;

		case MeasurementType::IMAGE_DISPLAY: // the last timing so the currentDataObject is written to the array and the dataIndex is incremented
			currentDataObject->imageDisplayTime = time.count();
			currentDataObject->frame = dataIndex;
			testData[dataIndex] = *currentDataObject;
			dataIndex++;

			//Data debug = *currentDataObject; //  used to debug the currentDataObject should be commented
			//std::cout << "debug active" << std::endl;

			break;

		default:
			break;
		}
	
		
	}


private:

	int calculateAVGFPS()
	{
		return frameCount;
	}
	
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;
	MeasurementType currentType;
	Data* currentDataObject;
	

	Data* testData;

	long* frameTime;   // array containing all time measurements in ns
	int dataIndex = 0;
	int frameCount;  // used while init frameTime array
	string testName;  
	string path;


};