// Chapter21.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Chapter21.h"
#include "Vector.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "_tmain()" << endl;

	MyCode::Vector<int> ints{ 1, 2, 3 };

	return 0;
}
