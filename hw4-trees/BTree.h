#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <exception>

#include <iostream>
#include <iomanip>

template <class T>
class BTree{
private:
	class Node{
	public:
		Node* leftChild;
		Node* rightChild;
		T dataValue;

		static unsigned	int maxID;
		unsigned int id;

		Node(const T &_dataValue) : leftChild(nullptr), rightChild(nullptr), dataValue(_dataValue) {
			id = maxID;
			maxID++;
		}

		unsigned int inline getId() const{
			return id;
		}
	};

	Node *root;

	Node& insert(const T &data, Node *&curr){
		if(curr == nullptr){
			curr = new Node(data);
			return *curr;
		}
		if(curr->dataValue == data)
			return *curr;
		if(data < curr->dataValue){
			return insert(data, curr->leftChild);
		}
		else{
			return insert(data, curr->rightChild);
		}
	}

	bool isLeaf(const Node *curr) const{
		return curr->leftChild == nullptr && curr->rightChild == nullptr;
	}

	Node*& rightMostNode(Node *&curr){
		if(curr->rightChild == nullptr)
			return curr;
		return rightMostNode(curr->rightChild);
	}

	void removeNode(Node *&curr){
		if(isLeaf(curr)){
			Node * tmp = curr;
			curr = nullptr;
			delete tmp;
			return;
		}
		if(curr->leftChild == nullptr){
			Node *tmp = curr;
			curr = curr->rightChild;
			delete tmp;
			return; 
		}
		Node *& rightMost = rightMostNode(curr->leftChild);
		curr->dataValue = rightMost->dataValue;
		remove(rightMost->dataValue, curr->leftChild);
	}

	bool remove(const T &data, Node *&curr){
		if(curr == nullptr){
			return false;
		}
		else if(curr->dataValue == data){
			removeNode(curr);
			return true;
		}
		else if(data > curr->dataValue){
			return remove(data, curr->rightChild);
		}
		else{
			return remove(data, curr->leftChild);
		}
	}

	size_t countNodes(const Node *curr) const{
		if(curr == nullptr){
			return 0;
		}
		return 1 + countNodes(curr->leftChild) + countNodes(curr->rightChild);
	}

	size_t countNodes(const std::function<bool(const T&)>& pred, const Node *curr) const{
		if(curr == nullptr){
			return 0;
		}
		if(pred(curr->dataValue))
			return 1;
		return countNodes(pred, curr->leftChild) + countNodes(pred, curr->rightChild);
	}

	size_t height(const Node *curr) const{
		if(curr == nullptr){
			return 0;
		}
		return 1 + std::max(height(curr->leftChild), height(curr->rightChild));
	}

	size_t countLeaves(const Node *curr) const{
		if(curr == nullptr)
			return 0;
		if(isLeaf(curr))
			return 1;
		return countLeaves(curr->leftChild) + countLeaves(curr->rightChild);
	}

	const T& maxLeaf(Node *curr) const{
		if(isLeaf(curr))
			return curr->dataValue;
		if(curr->leftChild != nullptr && curr->rightChild != nullptr)
			return std::max(maxLeaf(curr->leftChild), maxLeaf(curr->rightChild));
		else if(curr->leftChild)
			return maxLeaf(curr->leftChild);
		else
			return maxLeaf(curr->rightChild);
	}




// Trees 2 homework tasks




	std::vector<T> append(std::vector<T> lhs, std::vector<T> rhs) const{
		lhs.insert(lhs.end(), rhs.begin(), rhs.end());
		return lhs;
	}

	std::vector<T> leavesValues(Node *curr) const{
		if(curr == nullptr)
			return std::vector<T>();
		if(isLeaf(curr)){
			std::vector<T> res;
			res.push_back(curr->dataValue);
			return res;
		}
		return append(leavesValues(curr->leftChild), leavesValues(curr->rightChild));
	}

	std::string trace(const Node *curr, const T &pattern) const{
		if(curr == nullptr)
			return "X";
		if(curr->dataValue == pattern)
			return std::string();
		else if(pattern > curr->dataValue)
			return "R" + trace(curr->rightChild, pattern);
		else
			return "L" + trace(curr->leftChild, pattern);
	} 

	/*
	/// TRACE FUNCTION FOR RANDOM BINARY TREE
	std::string trace(const Node *curr, const T &pattern) const{
		if(curr == nullptr)
			return "X";
		if(curr->dataValue == pattern)
			return std::string();
		std::string leftSubTrace = trace(curr->leftChild, pattern);
		if(leftSubTrace != "X")
			return "L" + leftSubTrace;
		std::string rightSubTree = trace(curr->rightChild, pattern);
		if(rightSubTree != "X")
			return "R" + rightSubTree;
		else return "_";
	} 
	*/

	void prettyPrint(const Node *curr, size_t depth){
		if(curr == nullptr)
			return;
		prettyPrint(curr->rightChild, depth + 1);
		std::cout << std::setw(4 * depth);
		std::cout << std::endl;
		std::cout << curr->dataValue;
		std::cout << std::endl;
		prettyPrint(curr->leftChild, depth + 1);
		std::cout << std::setw(4 * depth);
	}

	T* at(Node *&curr, int& pos){
		if(curr == nullptr)
			return nullptr;
		if(pos == 0)
			return &curr->dataValue;
		pos -= 1;
		T *leftSubTree = at(curr->leftChild, pos);
		if(leftSubTree != nullptr)
			return leftSubTree;
		return at(curr->rightChild, pos);
	}

	std::vector<T> level(const Node *curr, const int k){
		if(curr == nullptr)
			return std::vector<T>();
		else if(k == 0){
			std::vector<T> res;
			res.push_back(curr->dataValue);
			return res;
		}
		else 
			return append(level(curr->leftChild, k - 1), 
						  level(curr->rightChild, k - 1));
	}




// Trees 2 homework tasks





	bool find(const Node*& curr, const T &pattern){
		if(curr == nullptr){
			return false;
		}
		else if(curr->dataValue == pattern)
			return true;
		else return find(curr->leftChild, pattern) || find(curr->rightChild, pattern);
	}

	static void printDotty(std::ostream &out, Node *curr){
		if(curr == nullptr)
			return;
		out << curr->getId() << "[label=\"" << curr->dataValue << "\"];" << std::endl;
		if (curr->leftChild != nullptr) {
			out << curr->getId() << "->" << curr->leftChild->getId() << "[color = \"red\"]" << ";" << std::endl;
		}
		if (curr->rightChild != nullptr){
			out << curr->getId() << "->" << curr->rightChild->getId() << ";" << std::endl;
		}
		printDotty(out, curr->leftChild);
		printDotty(out, curr->rightChild);
	}

public:
	BTree() : root(nullptr){

	}

	BTree(const BTree& rhs){

	}

	Node& insert(const T &data){
		return insert(data, root);
	}

	bool remove(const T &data){
		return remove(data, root);
	}

	size_t countNodes() const{
		return countNodes(root);
	}

	size_t countNodes(const std::function<bool(const T&)>& pred) const{
		return countNodes(pred, root);
	}

	size_t height() const{
		return height(root);
	}

	size_t countLeaves() const{
		return countLeaves(root);
	}

	const T& maxLeaf() const{
		return maxLeaf(root);
	}

	std::vector<T> leavesValues() const{
		return leavesValues(root);
	}

	void prettyPrint(){
		prettyPrint(root, 0);
	}

	std::string trace(const T &pattern) const{
		std::string str = trace(root,pattern);
		if(str.find("X") != std::string::npos)
			return "_";
		else 
			return str;
	}

	bool find(const T &pattern){
		return find(root, pattern);
	}

	T& operator[](int pos){
		T * res = at(root, pos);
		if(res != nullptr)
			return *(res);
		else
			throw std::out_of_range ("OUT OF RANGE\n");
	}

	std::vector<T> level(const int k){
		return level(root, k);
	}

	friend std::ostream& operator << (std::ostream &out, const BTree<T> &tree)
	{
		out << "digraph G {" << std::endl;
		printDotty(out, tree.root);
		out << "}" << std::endl;
		return out;
	}
	
	~BTree(){

	}
};

template <class T>
unsigned int BTree<T>::Node::maxID = 0;