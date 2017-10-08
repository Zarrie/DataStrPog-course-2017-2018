#include <iostream>
#include "list.h"

using namespace std;

void begin(const string& s)
{
	cout << endl;
	cout << " ========= TESTING METHOD " << s << " ========= " << endl;
}

void end(const string& s)
{
	cout << " ========= END OF TESTING METHOD " << s << " TEST ========= " << endl;
	cout << endl;
}

void cstrTest()
{
	::begin("constructor");
	cout << "constructing empty list\n";
	linkedList<int> list;
	::end("constructor");
}

void insertTest()
{
	::begin("insert");
	linkedList<int> list;
	cout << "Inserting elements from 0 to 9\n";
	for(int i = 0 ; i < 10 ; i++)
		list.insert(i);
	list.printAll();
	::end("insert");
}

void removeTest()
{
	::begin("remove");
	linkedList<int> list;
	for(int i = 0 ; i < 10 ; i++)
		list.insert(i);
	list.printAll();
	cout << "remove 0\n";
	list.remove(0);
	list.printAll();
	cout << "remove 5\n";
	list.remove(5);
	list.printAll();
	cout << "remove 9\n";
	list.remove(9);
	list.printAll();
	cout << "remove 10\n";
	list.remove(10);
	list.printAll();
	::end("remove");
}

void findTest()
{
	::begin("find");
	linkedList<int> list;
	list.range(1, 10);
	list.printAll();
	cout << "Find 5 : " << list.find(5) << endl;
	cout << "Find 15 : " << list.find(15) << endl;
	::end("find");
}

void sizeTest()
{
	::begin("size");
	linkedList<int> list;
	list.range(1, 10);
	cout << "Size of list\n";
	list.printAll();
	cout << "is : " << list.size() << endl;
	list.clear();
	cout << "Size of list\n";
	list.printAll();
	cout << "is : " << list.size() << endl;
	list.clear();
	list.range(1, 20);
	cout << "Size of list\n";
	list.printAll();
	cout << "is : " << list.size() << endl;
	::end("size");
}

void countTest()
{
	::begin("count");
	linkedList<int> list;
	for(int i = 0 ; i < 10 ; i++)
		list.insert(i);
	list.printAll();
	cout << "Count of el 15 " << list.count(15) << endl;
	cout << "Count of el 5 " << list.count(5) << endl;
	cout << "Count of el 0 " << list.count(0) << endl;
	cout << "Count of el 9 " << list.count(9) << endl;
	::end("count");
}

void rangeTest()
{
	::begin("range");
	linkedList<int> list;
	cout << "range 5, 15\n";
	list.range(5,15);
	list.printAll();
	list.clear();
	cout << "range 1, 10\n";
	list.range(1,10);
	list.printAll();
	::end("range");
}

void appendTest()
{
	::begin("append");
	linkedList<int> list1;
	list1.range(1, 10);
	list1.printAll();
	linkedList<int> list2;
	list2.range(11, 15);
	list2.printAll();
	list1.append(list2);
	list1.printAll();
	::end("append");
}

void concatTest()
{
	::begin("concat");
	linkedList<int> list1;
	list1.range(1, 10);
	list1.printAll();
	linkedList<int> list2;
	list2.range(11, 15);
	list2.printAll();
	linkedList<int> list3;
	list3.concat(list1,list2);
	list3.printAll();
	::end("concat");
}

void mapTest()
{
	::begin("map");
	linkedList<int> list1;
	list1.range(1, 10);
	list1.printAll();
	list1.map([](const int &x)->int { return (x * x); });
	list1.printAll();
	::end("map");
}

void reverseTest()
{
	::begin("reverse");
	linkedList<int> list;
	list.range(1, 10);
	list.printAll();
	list.reverse();
	list.printAll();
	linkedList<int> list2;
	list2.range(10, 18);
	list2.printAll();
	list2.reverse();
	list2.printAll();
	::end("reverse");
}

void duplicatesTest()
{
	::begin("duplicate");
	linkedList<int> list;
	list.range(1, 10);
	list.printAll();
	if(!list.duplicates())
		cout << "Has not duplicates\n";
	list.insert(5);
	list.printAll();
	if(list.duplicates())
		cout << "Has duplicates\n";
	::end("duplicate");
}

void removeDuplicatesTest()
{
	::begin("removeDuplicate");
	linkedList<int> list;
	list.range(1, 10);
	list.range(1, 10);
	list.printAll();
	list.removeDuplicates();
	list.printAll();
	::end("removeDuplicate");
}

void copyCstrTest()
{
	::begin("copy constructor");
	linkedList<int> list;
	list.range(1, 10);
	linkedList<int> list2 = list;
	list2.printAll();
	::end("copy constructor");
}

void eqOperatorTest()
{
	::begin("operator =");
	linkedList<int> list;
	list.range(1, 10);
	linkedList<int> list2;
	list2 = list;
	list2.printAll();
	::end("operator = ");
}

void isSortedTest()
{
	::begin("is sorted");
	linkedList<int> list;
	list.range(1, 10);
	list.printAll();
	if(list.isSorted())
		cout << "List is sorted\n";
	list.clear();
	list.range(5, 15);
	list.insert(4);
	list.printAll();
	if(!list.isSorted())
		cout << "List is not sorted\n";
	::end("is sorted");
}

void palindromeTest()
{
	::begin("palindrome");
	linkedList<int> list;
	list.range(1, 10);
	for(int i = 9 ; i >= 1 ; --i)
		list.insert(i);
	list.printAll();
	if(list.palindrome())
		cout << "List is palindrome!\n";
	list.clear();
	list.range(1, 10);
	for(int i = 8 ; i >= 1 ; --i)
		list.insert(i);
	list.printAll();
	if(!list.palindrome())
		cout << "List is not palindrome!\n";
	::end("palindrome");
}

int main()
{
	cstrTest();
	copyCstrTest();
	eqOperatorTest();
	insertTest();
	removeTest();
	sizeTest();
	findTest();
	countTest();
	rangeTest();
	appendTest();
	concatTest();
	mapTest();
	reverseTest();
	duplicatesTest();
	removeDuplicatesTest();
	isSortedTest();
	palindromeTest();

	return 0;
}
