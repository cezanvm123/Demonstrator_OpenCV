#pragma once
#include <string>
#include <opencv2/core/base.hpp>
using namespace std;

#define FRAME_COUNT 50

class Test
{
public: 
	Test(string testName, string path, int frameCount) : 
		testName(testName), path(path), frameCount(frameCount) 
	{
		frameTime = new int[frameCount];
	};
	virtual void runTest() = 0;

	void printResult()
	{
		std::cout << "*******************" << testName << "*******************" << std::endl;
		std::cout << "Amount of frames processed: " << dataIndex << std::endl;


		int totalMS = 0;
		for (int i = 0; i < dataIndex; i++)
		{
			totalMS += frameTime[i];
		}

		std::cout << "Total processing time: " << (float)totalMS / 1000.0 << "s" << std::endl;
		float avgFrameTime = (float)totalMS / (float)dataIndex;
		std::cout << "Average frame time: " << avgFrameTime << "ms" << std::endl;


		float avgFPS = 1000.0 / avgFrameTime;

		std::cout << "Average fps: " << avgFPS << "fps" << std::endl;
		std::cout << "-----------------------------------------------------------------" << std::endl << std::endl << std::endl;
	}

	string getPath()
	{
		return path;
	}

	string getTestName()
	{
		return testName;
	}

	void timingStart()
	{
		start = std::chrono::high_resolution_clock::now();
		
	}

	void timingStop()
	{
		end = std::chrono::high_resolution_clock::now();

		chrono::nanoseconds time = end - start;

		frameTime[dataIndex] = time / std::chrono::milliseconds(1);



		if (dataIndex == frameCount)
		{
			std::cout << "dataIndex will become to big and throw " << std::endl;
			throw;
		}
		dataIndex++;
		
	}

	int getFrameCount()
	{

	}
	
private:

	int calculateAVGFPS()
	{
		return frameCount;
	}
	
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;
	
	int* frameTime;   // array containing all time measurements
	int dataIndex = 0;
	int frameCount;  // used while init frameTime array
	string testName;  
	string path;


};