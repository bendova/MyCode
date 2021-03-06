// Chapter19.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <initializer_list>
#include "Array.h"
#include "Memory.h"
#include <memory>
#include <fstream>
#include <vector>

using namespace MyCode;

template<typename T>
struct MyStruct
{
	MyStruct(T value) : mValue(value)
	{}

	T& get();
private:
	T mValue;
};

template<typename T>
T& MyStruct<T>::get() 
{
	return mValue; 
}

class MyClass
{
public:
	MyClass() : mX(5)
	{
		std::cout << "MyClass::MyClass()" << std::endl;
	}
	~MyClass()
	{
		std::cout << "MyClass::~MyClass()" << std::endl;
	}

	void doSomething()
	{
		std::cout << "MyClass::doSomething() " << mX << std::endl;
	}
private:
	int mX;
};

std::unique_ptr<MyClass> getPointer()
{
	std::unique_ptr<MyClass> p{ new MyClass() };
	return p;
}

void testStdUniquePtr()
{
	std::unique_ptr<MyClass> p = getPointer();
	std::unique_ptr<MyClass> other{ std::move(p) };
}

UniquePointer<MyClass> getUniquePointer()
{
	UniquePointer<MyClass> p{ new MyClass() };
	return p;
}

void testMyUniquePointer()
{
	UniquePointer<MyClass> p = getUniquePointer();
	p->doSomething();
	(*p).doSomething();
	UniquePointer<MyClass> p2{ p.release() };
	p2.reset();
	p2->doSomething(); // should crash here because of the previous call to reset()
}

void testVectorIteration()
{
	using TestType = int;
	std::vector<TestType> v{ 1, 2, 3 };
	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		TestType x = *iter;
		x;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	testVectorIteration();
	std::getchar();
	return 0;
}

