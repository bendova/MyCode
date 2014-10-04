#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "Chapter21.h"
#include <vector>
#include <list>
#include <iterator>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(Chapter21UnitTest)
	{
	public:
		
		TEST_METHOD(TestFind)
		{
			std::vector<int> values1{ 1, 2, 3, 1 };
			auto iter1 = MyCode::find(values1.begin(), values1.end(), 1);
			Assert::IsTrue((iter1 == values1.begin()));

			std::vector<int> values2{ 1, 2, 3, 1 };
			auto iter2 = MyCode::find(values2.begin(), values2.end(), 5);
			Assert::IsTrue((iter2 == values2.end()));

			std::vector<int> values3{ 1, 2, 3, 1 };
			const int searchedValue = 3;
			auto iter3 = MyCode::find(values3.begin(), values3.end(), searchedValue);
			Assert::IsTrue((*iter3 == searchedValue));
		}

		TEST_METHOD(TestCount)
		{
			std::vector<int> values1{ 1, 2, 3, 1 };
			Assert::AreEqual(MyCode::count(values1.begin(), values1.end(), 1), 2u);

			std::vector<int> values2;
			Assert::AreEqual(MyCode::count(values2.begin(), values2.end(), 3), 0u);

			std::vector<int> values3{5, 5, 5};
			Assert::AreEqual(MyCode::count(values3.begin(), values3.end(), 5), 3u);

			std::vector<int> values4{ 7, 2, 7, 3, 7, 4, 7 };
			Assert::AreEqual(MyCode::count(values4.begin(), values4.end(), 7), 4u);
		}

		TEST_METHOD(TestCountIf)
		{
			std::vector<int> values1{ 1, 2, 3, 1 };

			unsigned occurrences = MyCode::count_if(values1.begin(), values1.end(), 
				[](int value) { return (value == 1); });
			Assert::AreEqual(occurrences, 2u);
		}

		TEST_METHOD(TestBinaryFindWithVector)
		{
			std::vector<int> values1{ 1, 2, 3, 4 };
			unsigned indexOfSearchedValue = 2;
			auto index1 = MyCode::binarySearch(values1, values1[indexOfSearchedValue]);
			Assert::IsTrue((index1 == indexOfSearchedValue));

			std::vector<int> values2{ 1, 2, 3, 4, 5 };
			auto index2 = MyCode::binarySearch(values2, 6);
			Assert::IsTrue((index2 == values2.size()));
		}

		TEST_METHOD(TestAdvance)
		{
			std::vector<int> vectorOfInts{ 1, 2, 3 };
			auto iterVector = vectorOfInts.begin();
			const unsigned step = 2;
			MyCode::advance(iterVector, step);
			Assert::AreEqual(*iterVector, vectorOfInts[step]);

			std::list<int> listOfInts{ 1, 2, 3 };
			auto iterList = listOfInts.begin();
			MyCode::advance(iterList, 2);
			Assert::AreEqual(*iterList, 3);
		}

		TEST_METHOD(TestBinaryFindWithList)
		{
			std::list<int> noValues{};
			Assert::IsFalse(MyCode::binarySearch(noValues.begin(), noValues.end(), 2));

			std::list<int> values{ 1, 2, 3, 4, 5 };
			Assert::IsFalse(MyCode::binarySearch(values.begin(), values.end(), 0));
			Assert::IsTrue(MyCode::binarySearch(values.begin(), values.end(), 1));
			Assert::IsTrue(MyCode::binarySearch(values.begin(), values.end(), 2));
			Assert::IsTrue(MyCode::binarySearch(values.begin(), values.end(), 3));
			Assert::IsTrue(MyCode::binarySearch(values.begin(), values.end(), 4));
			Assert::IsTrue(MyCode::binarySearch(values.begin(), values.end(), 5));
			Assert::IsFalse(MyCode::binarySearch(values.begin(), values.end(), 6));
		}
	};
}