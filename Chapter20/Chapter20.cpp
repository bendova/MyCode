// Chapter20.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, vector<T>& v)
{
	out << "{ ";
	unsigned lastIndex = v.size() - 1;
	for (unsigned i = 0; i < lastIndex; ++i)
	{
		cout << v[i] << ", ";
	}
	cout << v[lastIndex] << " }";

	return out;
}

template<typename T>
istream& operator>>(istream& in, vector<T>& v)
{
	T valueRead;
	while (in >> valueRead)
	{
		v.push_back(valueRead);
	}
	return in;
}

namespace MyCode
{
	void testVectorInOutOperators()
	{
		vector<int> v;
		cout << "Insert integer values for vector: " << endl;
		cin >> v;

		cout << "You entered the following values: " << v << endl;
	}

	struct Record
	{
		double mUnitPrice;
		unsigned mUnitsSold;
	};

	double getPrice(double initialValue, const Record& record)
	{
		return (initialValue + record.mUnitPrice * record.mUnitsSold);
	}

	template<typename Iter, typename T = iterator_traits<Iter>::value_type, typename BinaryOperation = std::plus<T>>
	T accumulate(Iter begin, Iter end, T initialValue = T(), BinaryOperation operation = BinaryOperation())
	{
		T sum = initialValue;
		while (begin != end)
		{
			sum = operation(sum, *begin++);
		}
		return sum;
	}

	void testAccumulate()
	{
		vector<Record> records;
		records.push_back(Record{ 1.0, 1 });
		records.push_back(Record{ 2.0, 2 });
		records.push_back(Record{ 3.0, 2 });
		double totalOfRecords = accumulate(records.begin(), records.end(), 0.0, getPrice);

		vector<double> doubles = { 1.0, 2.0, 7.0 };
		double totalOfDoubles = accumulate(doubles.begin(), doubles.end());

		vector<int> ints = { 1, 2, 7 };
		int totalOfInts = accumulate(ints.begin(), ints.end());
	}

	void myCopy(int* begin1, int* end1, int* begin2)
	{
		while (begin1 != end1)
		{
			*begin2++ = *begin1++;
		}
	}

	void testMyCopy()
	{
		const int arraySize = 5;
		unique_ptr<int> array1{ new int[arraySize] };
		unique_ptr<int> array2{ new int[arraySize] };

		for (int i = 0; i < arraySize; ++i)
		{
			(&(*array1))[i] = i;
		}

		myCopy(&(*array1), (&(*array1) + arraySize), &(*array2));
	}

	template<typename Iter>
	void advance(Iter &iter, int n)
	{
		if (n > 0)
		{
			while (--n > 0)
			{
				++iter;
			}
		}
		else if (n < 0)
		{
			while (++n < 0)
			{
				--iter;
			}
		}
	}

	void testAdvance()
	{
		vector<int> values = { 1, 2, 3, 4 };
		auto iterator = values.begin();

		advance(iterator, 3);
		cout << *iterator << " is correct " << ((*iterator == 3) ? "true" : "false") << endl;

		advance(iterator, -3);
		cout << *iterator << " is correct " << ((*iterator == 1) ? "true" : "false") << endl;
	}

	unsigned countElements(char *x)
	{
		unsigned count = 0;
		while (*x++ != NULL)
		{
			++count;
		}
		return count;
	}

	bool compare(char *what, char *to)
	{
		while (*what && *to)
		{
			if (*what++ != *to++)
			{
				return false;
			}
		}
		return true;
	}

	char* makeCopy(char *x)
	{
		unsigned size = countElements(x);
		if (size > 0)
		{
			char *copy = new char(size);
			char *iter = copy;
			while (*iter++ = *x++)
			{}
			return copy;
		}
		return nullptr;
	}

	void checkForCharArray(char *x)
	{
		unsigned count = countElements(x);
		bool isHello = compare(x, "Hello");
		bool isHowdy = compare(x, "Howdy");
		char* copy = makeCopy(x);
	}

	void testCheckForCharArray()
	{
		char charArray[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
		checkForCharArray(charArray);
	}

	template<typename Iter1, typename Iter2>
	Iter2 copy(Iter1 begin1, Iter1 end1, Iter2 begin2)
	{
		while (begin1 != end1)
		{
			*begin2 = *begin1;
			begin1++;
			begin2++;
		}
		return begin2;
	}

	void testCopy()
	{
		vector<int> a1{ 1, 2, 3, 4, 5 };
		vector<int> a2{ 0, 0, 0, 0, 0 };

		MyCode::copy(a1.begin(), a1.end(), a2.begin());

		cout << a2 << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "main()" << endl;
	
	getchar();
	return 0;
}

