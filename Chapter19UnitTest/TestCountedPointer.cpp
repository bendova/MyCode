#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "CountedPointer.h"
#include <memory>

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace TestCountedPointer
{
	class MyClass
	{
	public:
		MyClass(int x, int y = 0) : mValue( x )
		{
			std::cout << "MyClass()" << std::endl;
		}
		~MyClass()
		{
			std::cout << "~MyClass()" << std::endl;
		}
	private:
		int mValue;
	};

	TEST_CLASS(TestCountedPointer)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			using TestType = int;
			CountedPointer<TestType> myPtr(1);
			Assert::AreEqual(*myPtr, 1);

			myPtr.~CountedPointer();
			Assert::IsNull(myPtr.operator->());
		}
		
		TEST_METHOD(TestCopyConstructor)
		{
			using TestType = int;
			CountedPointer<TestType> myPtr(1);
			Assert::AreEqual(*myPtr, 1);

			TestType* pointerToValue = myPtr.operator->();

			CountedPointer<TestType> otherPtr{ myPtr };

			myPtr.~CountedPointer();
			Assert::IsNull(myPtr.operator->());
			Assert::AreEqual(*pointerToValue, 1);

			otherPtr.~CountedPointer();
			Assert::IsNull(otherPtr.operator->());
			Assert::AreNotEqual(*pointerToValue, 1);
		}

		TEST_METHOD(TestMoveConstructor)
		{
			using TestType = MyClass;
			CountedPointer<TestType> myPtr(1);

			CountedPointer<TestType> otherPtr{ std::forward<CountedPointer<TestType>>(myPtr) };
		}
	};
}