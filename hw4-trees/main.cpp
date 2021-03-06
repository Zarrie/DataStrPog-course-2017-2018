#include "BTree.h"

//#include "AST.h"

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

void BTreeLeavesValuesTest()
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
	for(auto it : tree.leavesValues())
		std::cout << it << " ";
	std::cout << std::endl;
}

void BTreeTraceTest()
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
	std::string s = tree.trace(19);
	std::cout << s << std::endl;
	tree.prettyPrint();
}

void BTreeIndOpTest()
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
	for(int i = 0 ; i < 8 ; ++i){
		//try{
			std::cout << tree[i] << " ";
		//}
		//catch (...){
		//	continue;
		//}
	}
	std::cout <<  std::endl;
}

void BTreeLevelTest()
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
	std::vector<int> level1 = tree.level(2);
	for(auto it : level1)
		std::cout << it << " ";
	std::cout << std::endl;
}

void subTreeSizeTest()
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

	tree.subTreeSize();
	std::cout << tree;
}

void equalLevelsTest()
{
	BTree<int> tree;
	tree.insert(5);
	tree.insert(5);
	tree.insert(5);
	tree.insert(5);
	std::cout << tree.equalLevels() << std::endl;
}

void isBSTTest()
{
	BTree<int> tree;
	/*tree.insert(15);
	tree.insert(12);
	tree.insert(24);
	tree.insert(3);
	tree.insert(13);
	tree.insert(36);
	tree.insert(16);
	tree.insert(19);*/
	std::cout << tree.isBST() << std::endl;
}

void treeIteratorTest()
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

	BTree<int>::TreeIterator it = tree.begin("inorder");
	while(it != tree.end()){
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	it = tree.begin("preorder");
	while(it != tree.end()){
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	it = tree.begin("postorder");
	while(it != tree.end()){
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	it = tree.begin("leavesOnly");
	while(it != tree.end()){
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	BTree<int>::TreeIterator it_pred = tree.begin("inorder", [](const int& x)->bool{ return !(x%2); });
	while(it_pred != tree.end()){
		std::cout << *it_pred << " ";
		it_pred++;
	}
	std::cout << std::endl;

	it_pred = tree.begin("postorder", [](const int& x)->bool{ return !(x%2); });
	while(it_pred != tree.end()){
		std::cout << *it_pred << " ";
		it_pred++;
	}

	std::cout << std::endl;
	it_pred = tree.begin("preorder", [](const int& x)->bool{ return !(x%2); });
	while(it_pred != tree.end()){
		std::cout << *it_pred << " ";
		it_pred++;
	}

	std::cout << std::endl;
	it_pred = tree.begin("leavesOnly", [](const int& x)->bool{ return !(x%2); });
	while(it_pred != tree.end()){
		std::cout << *it_pred << " ";
		it_pred++;
	}
	std::cout << std::endl;

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
	BTreeLeavesValuesTest();
	BTreeTraceTest();
	BTreeIndOpTest();
	BTreeLevelTest();
	subTreeSizeTest();
	equalLevelsTest();
	isBSTTest();
*/
	treeIteratorTest();

	return 0;
}