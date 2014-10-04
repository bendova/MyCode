// Chapter10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Chapter10.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "_tmain()" << endl;

	const unsigned divisions = 10;
	float x = 1.0f / divisions;
	float sum = 0.0f;
	for (unsigned i = 0; i < divisions; ++i)
	{
		sum += x;
	}

	cout << setprecision(15) << sum << endl;

	return 0;
}

bool MyCode::WriteIntegersToFile(const std::string& filePath, const vector<int>& values, const std::string& valueSeparator)
{
	bool succes = false;
	ofstream fileToWrite;
	fileToWrite.open(filePath, ofstream::out);
	if (fileToWrite.good())
	{
		succes = true;
		for (auto iter = values.begin(); iter != values.end(); ++iter)
		{
			fileToWrite << *iter << valueSeparator;
		}
	}
	fileToWrite.close();
	return succes;
}

std::vector<int> MyCode::ReadIntegersFromFile(const std::string& filePath)
{
	std::vector<int> valuesRead;
	ifstream fileToRead{ filePath };
	
	int value;
	fileToRead >> value;
	while (fileToRead.good())
	{
		valuesRead.push_back(value);
		fileToRead >> value;
	}
	return valuesRead;
}

int MyCode::GetSumOfIntegersFromFile(const std::string& filePath)
{
	std::vector<int> valuesRead = ReadIntegersFromFile(filePath);
	int sumOfValues = 0;
	
	auto iter = valuesRead.begin();
	auto end = valuesRead.end();
	while (iter != end)
	{
		sumOfValues += *iter++;
	}
	return sumOfValues;
}

