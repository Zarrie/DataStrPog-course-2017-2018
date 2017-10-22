#include <iostream>
#include <string>

#include <cassert>

#include "array.h"

using namespace std;

void begin(const string& s)
{
	cout << endl;
	cout << " ========= TESTING METHOD " << s << " ========= " << endl;
	cout << endl;
}

void end(const string& s)
{
	cout << endl;
	cout << " ========= END OF TESTING METHOD " << s << " ========= " << endl;
	cout << endl;
}

void arrayCstrTest()
{
	::begin("arrayCstr");
	array<int> arr(10);
	::end("arrayCstr");
}

void arrayOpTest()
{
	::begin("operator[]");
	array<int> arr(10);
	for(int i = 0 ; i < 10 ; ++i)
		arr[i] = i;
	arr.printAll();
	::end("operator[]");
}

void copyCstrTest()
{
	::begin("copyCstr");
	array<int> arr(10);
	for(int i = 0 ; i < 10 ; ++i)
		arr[i] = i;
	array<int> arrCopy = arr;
	for(int i = 0 ; i < 10 ; ++i)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	assert(arr.Size() == arrCopy.Size());
	::end("copyCstr");
}

void assignementOpTest()
{
	::begin("operator=");
	array<int> arr(10);
	for(int i = 0 ; i < 10 ; ++i)
		arr[i] = i;
	array<int> arrCopy(10);
	arrCopy = arr;
	for(int i = 0 ; i < 10 ; ++i)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	assert(arr.Size() == arrCopy.Size());
	::end("operator=");
}

void iteratorTest()
{
	::begin("iterator");
	array<int> arr(10);
	array<int>::arrayIterator it = arr.begin();
	int i = 0;
	while(it != arr.end())
	{
		*it = i++;
		++it;
	}
	it = arr.begin();
	while(it != arr.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << *it;
	std::cout << std::endl;
	it = arr.end();
	while(it != arr.begin())
	{
		std::cout << *it << " ";
		--it;
	}
	std::cout << *it;
	std::cout << std::endl;
	::end("iterator");
}

int main()
{
	arrayCstrTest();
	arrayOpTest();
	copyCstrTest();
	assignementOpTest();
	iteratorTest();

	return 0;
}