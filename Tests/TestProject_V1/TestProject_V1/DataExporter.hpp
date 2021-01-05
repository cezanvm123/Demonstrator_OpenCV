#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Data
{
public:
	long imageLoadTime;				// in ns
	long imageConvertionTime;		// in ns
	long kernelCalculationTime;		// in ns
	long imageDisplayTime;			// in ns

	int frame;
};




class DataExporter
{
public:

	static void writeData(Data* list, int listCount, std::string name)
	{
		std::string csvData = convertToCSV(list, listCount);
		
		writeToFile(name + ".csv", csvData);
	}

private:

	static std::string convertToCSV(Data* list, int listCount)
	{
		std::string data = "frame,image load Time,image convertion time,kernel calculation time,image display time \n";

		for (int i = 0; i < listCount; i++)
		{
			data += std::to_string(list[i].frame) + "," + std::to_string((double)list[i].imageLoadTime / 1000000.0) + "," + std::to_string((double)list[i].imageConvertionTime / 1000000.0) + "," + std::to_string((double)list[i].kernelCalculationTime / 1000000.0) + "," + std::to_string((double)list[i].imageDisplayTime / 1000000.0);
			data += "\n";
		}
		return data;
	}

	static void writeToFile(std::string fileName, std::string data)
	{
		//std::string path = "";      // Linux path 
		std::string path = "D:\\School\\Signals\\Demonstrator_OpenCV\\OutputData\\";		  // windows path this is temp just as debug

		std::ofstream myfile;
		myfile.open(path + fileName);
		myfile << data;
		myfile.close();

	}

	
};