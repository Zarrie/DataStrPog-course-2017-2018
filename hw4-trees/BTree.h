#pragma once

#include <fstream>
#include <functional>

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

	bool find(const Node*& curr, const T &pattern){
		if(curr == nullptr){
			return false;
		}
		else if(curr->dataValue == pattern)
			return true;
		else return find(curr->leftChild, pattern) || find(curr->rightChild, pattern);
	}

	// IF NOT STATIC DOES NOT WORK - WHY ?!?!?
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

	bool find(const T &pattern){
		return find(root, pattern);
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
/*
template <class T>
std::ostream& operator << (std::ostream &out, const BTree<T> &tree)
{
	out << "digraph G {" << std::endl;
	printDotty(out, tree.root);
	out << "}" << std::endl;
	return out;
}*/