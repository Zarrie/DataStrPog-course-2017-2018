#pragma once

#include <functional>

template <class T>
class BTree{
private:
	class Node{
	public:
		Node* leftChild;
		Node* rightChild;
		T dataValue;

	public:
		Node(const T &_dataValue) : leftChild(nullptr), rightChild(nullptr), dataValue(_dataValue) {}
	};

	Node *root;

	Node& insert(const T &data, Node *&curr){
		if(curr == nullptr){
			curr = new Node(data);
			return *curr;
		}
		if(data < curr->dataValue){
			return insert(data, curr->leftChild);
		}
		else{
			return insert(data, curr->rightChild);
		}
	}

	Node*& rightMostNode(Node *&curr){
		if(curr->rightChild == nullptr)
			return curr;
		return rightMostNode(curr->rightChild);
	}

	void removeNode(Node *&curr){
		Node *& rightMost = rightMostNode(curr->leftChild);
		curr->dataValue = rightMost->dataValue;
		delete rightMost;
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

	bool isLeaf(const Node *curr) const{
		return curr->leftChild == nullptr && curr->rightChild == nullptr;
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

	~BTree(){

	}
};
