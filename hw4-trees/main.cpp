#include "BTree.h"

#include <iostream>
#include <time.h>
#include <cstdlib>

void BTreeCstrTest()
{
	BTree<int> IntTree;
	BTree<char> charTree;
	BTree<BTree<int>> TreeTree;
}

void BTreeInsertTest()
{
	BTree<int> tree;
	for(int i = 0 ; i < 10 ; ++i)
		tree.insert(i);

	for(int i = 0 ; i < 10000 ; ++i)
		tree.insert(rand());
	std::cout << tree.countNodes() << std::endl;
}

void BTreeRemoveTest()
{
	BTree<int> tree;
	tree.insert(15);
	tree.insert(12);
	tree.insert(24);
	tree.insert(3);
	tree.insert(13);
	tree.insert(36);
	tree.insert(16);
	tree.insert(19);
	//std::cout << tree;
	tree.remove(24);
	std::cout << tree;
}

void BTreeHeightTest()
{
	BTree<int> tree;
	for(int i = 0 ; i < 10 ; ++i)
		tree.insert(i);
	std::cout << tree.height() << std::endl;
}

void BTreeLeavesCountTest()
{
	BTree<int> tree;
	for(int i = 0 ; i < 10 ; ++i)
		tree.insert(i);
	std::cout << tree.countLeaves() << std::endl;
}

void BTreeMaxLeafTest()
{
	BTree<int> tree;
	for(int i = 0 ; i < 10 ; ++i)
		tree.insert(i);
	std::cout << tree.maxLeaf() << std::endl;
}

void BTreePrintTest()
{
	BTree<int> tree;
	for(int i = 0 ; i < 100 ; ++i)
		tree.insert(rand() % 1024);
	std::cout << tree;
}

int main(){
	srand(time(NULL));
/*
	BTreeCstrTest();
	BTreeInsertTest();
	BTreeRemoveTest();
	BTreeHeightTest();
	BTreeLeavesCountTest();
	BTreeMaxLeafTest();
	BTreePrintTest();
*/

	BTreeRemoveTest();
	return 0;
}