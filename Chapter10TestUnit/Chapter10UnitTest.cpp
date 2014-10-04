#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include "Chapter10.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace UnitTest
{		
	TEST_CLASS(Chapter10UnitTest)
	{
	private:
		const std::string mFilePath = "IntegersFile.txt";

	public:
		void DeleteFile(const std::string& filePath)
		{
			if (std::remove(filePath.c_str()) == 0)
			{
				std::cout << "DeleteFile() Successfuly deleted " << filePath << std::endl;
			}
		}

		~Chapter10UnitTest()
		{
			DeleteFile(mFilePath);
		}

		bool AreVectorsEqual(const std::vector<int>& vector1, const std::vector<int>& vector2)
		{
			bool areEqual = true;
			if (vector1.size() == vector2.size())
			{
				auto iter1 = vector1.begin();
				auto end1 = vector1.end();

				auto iter2 = vector2.begin();
				while (iter1 != end1)
				{
					if (*iter1++ != *iter2++)
					{
						areEqual = false;
						break;
					}
				}
			}
			else
			{
				areEqual = false;
			}
			return areEqual;
		}

		TEST_METHOD(TestComparisonOfVectors)
		{
			std::vector<int> v1{ 1, 2, 3 };
			std::vector<int> v2{ 1, 2, 3 };
			Assert::IsTrue(AreVectorsEqual(v1, v2));

			std::vector<int> v3{ 1 };
			Assert::IsFalse(AreVectorsEqual(v1, v3));

			std::vector<int> v4;
			std::vector<int> v5;
			Assert::IsTrue(AreVectorsEqual(v4, v5));
		}

		TEST_METHOD(TestWritingIntegersToFile)
		{
			std::vector<int> valuesWritten {1, 2};
			Assert::IsTrue(WriteIntegersToFile(mFilePath, valuesWritten, std::string{" "}));

			std::vector<int> valuesRead = ReadIntegersFromFile(mFilePath);

			Assert::IsTrue(AreVectorsEqual(valuesWritten, valuesRead));
		}

		TEST_METHOD(TestSumOfIntegersReadFromFile)
		{
			std::vector<int> valuesWritten{ 1, 2 };
			Assert::IsTrue(WriteIntegersToFile(mFilePath, valuesWritten, std::string{ " " }));

			Assert::AreEqual(GetSumOfIntegersFromFile(mFilePath), 3);
		}
	};
}