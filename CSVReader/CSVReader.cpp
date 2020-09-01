#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
std::vector<std::vector<std::string>> CSVReader::getData()
{
	std::ifstream file(fileName);
	std::vector<std::vector<std::string>> dataList;

	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string str = "";
		std::vector<std::string> vec;
		while(std::getline(ss, str, ',')) {
			vec.push_back(str);
		}
		dataList.push_back(vec);
	}
	// Close the File
	file.close();
	return dataList;
}

//int main()
//{
//	CSVReader reader("ticks.csv");
//
//	// Get the data from CSV File
//	std::vector<std::vector<std::string> > dataList = reader.getData();
//
//	// Print the content of row by row on screen
//	for (std::vector<std::string> vec : dataList)
//	{
//		for (std::string data : vec)
//		{
//			std::cout << data << " , ";
//		}
//		std::cout << std::endl;
//
//	}
//	system("pause");
//	return 0;
//}