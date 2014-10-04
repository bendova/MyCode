#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "Allocator.h"
#include "Vector.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MyCode;

namespace AllocatorTest
{
	class MyClass
	{
	public:
		MyClass() : mValue(0)
		{
			std::cout << "MyClass()" << std::endl;
		}
		MyClass(const MyClass& other) : mValue(other.mValue)
		{
			std::cout << "MyClass(const MyClass& other)" << std::endl;
		}
		MyClass(MyClass&& other) : mValue(other.mValue)
		{
			std::cout << "MyClass(yClass&& other)" << std::endl;
		}

		~MyClass()
		{
			std::cout << "~MyClass()" << std::endl;
		}
	private:
		int mValue;
	};

	TEST_CLASS(AllocatorTest)
	{
	public:
		
		TEST_METHOD(TestAllocationWithEmptyArena)
		{
			const unsigned arenaSize = 0;

			typedef int TestType;
			Allocator<TestType> myAllocator(new Arena{arenaSize});

			TestType* allocatedSpace = myAllocator.allocate(1);
			Assert::IsNull(allocatedSpace);
		}

		TEST_METHOD(TestAllocation)
		{
			const unsigned arenaSize = 20;

			typedef int TestType;
			Allocator<TestType> myAllocator(new Arena{ arenaSize });

			TestType* allocatedSpace = myAllocator.allocate(1);
			Assert::IsNotNull(allocatedSpace);
		}

		TEST_METHOD(TestSequentialDeallocation)
		{
			const unsigned arenaSize = 88;
			
			typedef int TestType;
			Allocator<TestType> myAllocator(new Arena{ arenaSize });

			TestType *allocatedSpace1 = allocateAndInit(myAllocator, 1);
			TestType *allocatedSpace2 = allocateAndInit(myAllocator, 3);
			TestType *allocatedSpace3 = allocateAndInit(myAllocator, 2);
			TestType *allocatedSpace4 = allocateAndInit(myAllocator, 5);

			myAllocator.deallocate(allocatedSpace2);
			myAllocator.deallocate(allocatedSpace3);
			myAllocator.deallocate(allocatedSpace4);
			myAllocator.deallocate(allocatedSpace1);
			Assert::AreEqual(myAllocator.getTotalFreeSpace(), arenaSize);
			Assert::AreEqual(myAllocator.getAvailableFreeSpace(), (arenaSize - Allocator<TestType>::BYTES_OF_OVEHEAD_PER_ALLOCATION));
		}

		TEST_METHOD(TestRandomDeallocation)
		{
			const unsigned arenaSize = 88;

			using TestType = int;
			Allocator<TestType> myAllocator(new Arena{ arenaSize });

			TestType *allocatedSpace1 = allocateAndInit(myAllocator, 1);
			TestType *allocatedSpace2 = allocateAndInit(myAllocator, 3);
			TestType *allocatedSpace3 = allocateAndInit(myAllocator, 2);
			TestType *allocatedSpace4 = allocateAndInit(myAllocator, 5);

			myAllocator.deallocate(allocatedSpace1);
			myAllocator.deallocate(allocatedSpace3);
			myAllocator.deallocate(allocatedSpace2);
			myAllocator.deallocate(allocatedSpace4);
			Assert::AreEqual(myAllocator.getTotalFreeSpace(), arenaSize);
			Assert::AreEqual(myAllocator.getAvailableFreeSpace(), (arenaSize - Allocator<TestType>::BYTES_OF_OVEHEAD_PER_ALLOCATION));
		}

		template<typename T>
		T* allocateAndInit(Allocator<T>& allocator, unsigned itemsCount)
		{
			T* allocatedSpace = allocator.allocate(itemsCount);
			Assert::IsNotNull(allocatedSpace);

			for (unsigned i = 0; i < itemsCount; ++i)
			{
				allocatedSpace[i] = T(i);
			}

			return allocatedSpace;
		}

		TEST_METHOD(TestObjectConstruction)
		{
			const unsigned arenaSize = 88;

			using TestType = MyClass;
			Allocator<TestType> myAllocator(new Arena{ arenaSize });

			MyClass *defaultConstructedObject = nullptr;
			myAllocator.construct(defaultConstructedObject);
			Assert::IsNotNull(defaultConstructedObject);

			MyClass *copyConstructedObject = nullptr;
			MyClass initialValue;
			myAllocator.construct(copyConstructedObject, initialValue);
			Assert::IsNotNull(copyConstructedObject);

			MyClass *moveConstructedObject = nullptr;
			myAllocator.construct(moveConstructedObject, MyClass());
			Assert::IsNotNull(moveConstructedObject);

			myAllocator.destroy(defaultConstructedObject);
			Assert::IsNull(defaultConstructedObject);

			myAllocator.destroy(copyConstructedObject);
			Assert::IsNull(copyConstructedObject);

			myAllocator.destroy(moveConstructedObject);
			Assert::IsNull(moveConstructedObject);

			Assert::AreEqual(myAllocator.getTotalFreeSpace(), arenaSize);
			Assert::AreEqual(myAllocator.getAvailableFreeSpace(), (arenaSize - Allocator<TestType>::BYTES_OF_OVEHEAD_PER_ALLOCATION));
		}
	};
}