#include "stdafx.h"
#include "CppUnitTest.h"
#include "FileHandle.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace FileHandleTest
{
	TEST_CLASS(FileHandleTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			std::string filePath = "D:\\file.txt";
			FileHandle file{ filePath };
		}
	};
}