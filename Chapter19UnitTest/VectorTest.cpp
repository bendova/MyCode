#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace VectorTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		
		MyCode::Vector<int> getVector(std::initializer_list<int> list)
		{
			MyCode::Vector<int> newVector{ list };
			return newVector;
		}
		
		TEST_METHOD(TestBasicOperationsOnVector)
		{
			Vector<int> v0;
			Vector<int> v1(1);
			Vector<int> v2{ 1, 2 };
			Vector<int> v3{ v1 };
			
			v3[0] = 2;
			
			Vector<int> v4 = getVector({ 3, 4, 5 });
			v4.reserve(8);
			v4.push_back(5);
			v4.resize(16, 17);
			
			std::cout << v4 << std::endl;
		}
		
		template<typename T>
		void addElements(Vector<T>& left, const Vector<T>& right)
		{
			int leftSize = left.size();
			int rightSize = right.size();
			int itemsToAddCount = ((leftSize > rightSize) ? rightSize : leftSize);
			for (int i = 0; i < itemsToAddCount; ++i)
			{
				left[i] += right[i];
			}
		}

		template<typename T>
		T getSumOfElementsProduct(const Vector<T>& left, const Vector<T>& right)
		{
			int leftSize = left.size();
			int rightSize = right.size();
			int itemsToAddCount = ((leftSize > rightSize) ? rightSize : leftSize);

			T sum = T();
			for (int i = 0; i < itemsToAddCount; ++i)
			{
				sum += left[i] * right[i];
			}
			return sum;
		}

		TEST_METHOD(TestAddingVectorElements)
		{
			Vector<int> v1{ 1, 2, 3, 4 };
			Vector<int> v2{ 5, 6, 7, 8 }; 
			addElements(v1, v2);
			Assert::AreEqual(v1[0], 6);
			Assert::AreEqual(v1[1], 8);
			Assert::AreEqual(v1[2], 10);
			Assert::AreEqual(v1[3], 12);
		}

		TEST_METHOD(TestMultiplyingVectorElements)
		{
			Vector<int> v1{ 1, 2, 3, 4 };
			Vector<int> v2{ 5, 6, 7, 8 }; // 5 + 12 + 21 + 32 = 70
			int sumOfProducts = getSumOfElementsProduct(v1, v2);
			Assert::AreEqual(sumOfProducts, 70);
		}

		TEST_METHOD(TestForwardIteration)
		{
			Vector<int> v1{ 1, 2, 3 };

			Vector<int>::iterator iter = v1.begin();
			Vector<int>::iterator end = v1.end();
			for (int i = 0; iter != end; ++i, ++iter)
			{
				Assert::AreEqual(v1[i], *iter);
			}
		}

		TEST_METHOD(TestBackwardIteration)
		{
			Vector<int> v1{ 1, 2, 3 };

			Vector<int>::reverse_iterator iter = v1.rbegin();
			Vector<int>::reverse_iterator end = v1.rend();

			for (int i = v1.size() - 1 ; iter != end; --i, ++iter)
			{
				Assert::AreEqual(v1[i], *iter);
			}
		}
	};
}