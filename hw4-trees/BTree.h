#pragma once

#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <string>
#include <functional>
#include <exception>
#include <unordered_set>
#include <iostream>
#include <iomanip>
#include <limits.h>

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
		//Allow/Forbid elements duplication
		/*if(curr->dataValue == data)
			return *curr;*/
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

	std::vector<T> level(const Node *curr, const int depth){
		if(curr == nullptr)
			return std::vector<T>();
		else if(depth == 0){
			std::vector<T> res;
			res.push_back(curr->dataValue);
			return res;
		}
		else 
			return append(level(curr->leftChild, depth - 1), 
						  level(curr->rightChild, depth - 1));
	}




// Trees 2 homework tasks


// Trees 3 homework tasks

	std::unordered_set<T> appendSets(const std::unordered_set<T> &lhs, const std::unordered_set<T> &rhs){
		std::unordered_set<T> res;
		res.insert(lhs.begin(), lhs.end());
		res.insert(rhs.begin(), rhs.end());
		return res;
	}

	std::unordered_set<T> levelUniques(const Node *curr, const int depth){
		if(curr == nullptr)
			return std::unordered_set <T>();
		else if(depth == 0){
			std::unordered_set <T> res;
			res.insert(curr->dataValue);
			return res;
		}
		else 
			return appendSets(levelUniques(curr->leftChild, depth - 1), 
						  levelUniques(curr->rightChild, depth - 1));
	}

	bool isBST(const Node *curr, std::pair<int, int> bounds) const{
		if(curr == nullptr)
			return true;
		else{
			return curr->dataValue < bounds.second && curr->dataValue >= bounds.first &&
			isBST(curr->leftChild, std::pair<int, int>(bounds.first, std::min(curr->dataValue, bounds.second))) &&
			isBST(curr->rightChild, std::pair<int, int>(std::max(curr->dataValue, bounds.first), bounds.second));
		}
	}


	void buildBalancedText(const std::string &str){

	}

public:
	int equalLevels(){
		int h = height(root), result = 0;
		for(int i = 0 ; i < h - 1 ; ++i){
			for(int j = i + 1 ; j < h ; ++j){
				if(levelUniques(root, i) == levelUniques(root, j))
					result++;
			}
		}
		return result;
	}

	bool isBST() const{
		return isBST(root, std::make_pair(INT_MIN, INT_MAX));
	}

private:
	unsigned int subTreeSize(Node *&curr){
		if(curr == nullptr)
			return 0;
		if(isLeaf(curr)){
			curr->dataValue = 1;
			return 1;
		}
		curr->dataValue = subTreeSize(curr->leftChild) + subTreeSize(curr->rightChild) + 1;
		return curr->dataValue;
	}


// Trees 3 homework tasks




// Trees 4 homework tasks

public:
	class TreeIterator{
	private:
		std::stack< std::pair< Node*, bool> > state;
		std::string traversal;
		std::function<bool(const T&)> Pred;
		Node *root_;

		void getNext(){
			//do{
			if(traversal == "inorder")
				getNextInorder();
			else if(traversal == "preorder")
				getNextPreorder();
			else if(traversal == "postorder")
				getNextPostorder();
			else if (traversal == "leavesOnly")
				getNextLeavesOnly();
			//} while(!state.empty() || Pred(state.top().first->dataValue) == true);
		}

		void getNextInorder(){
			while(!state.empty() && state.top().second == false){
				std::pair< Node *, bool> curr = state.top();
				state.pop();
				if(curr.first->rightChild != nullptr)
					state.push(std::make_pair(curr.first->rightChild, false));
				state.push(std::make_pair(curr.first, true));
				if(curr.first->leftChild != nullptr)
					state.push(std::make_pair(curr.first->leftChild, false));
			}
		}

		void getNextPreorder(){
			while(!state.empty() && state.top().second == false){
				std::pair< Node *, bool> curr = state.top();
				state.pop();
				if(curr.first->rightChild != nullptr)
					state.push(std::make_pair(curr.first->rightChild, false));
				if(curr.first->leftChild != nullptr)
					state.push(std::make_pair(curr.first->leftChild, false));
				state.push(std::make_pair(curr.first, true));
			}
		}

		void getNextPostorder(){
			while(!state.empty() && state.top().second == false){
				std::pair< Node *, bool> curr = state.top();
				state.pop();
				state.push(std::make_pair(curr.first, true));
				if(curr.first->rightChild != nullptr)
					state.push(std::make_pair(curr.first->rightChild, false));
				if(curr.first->leftChild != nullptr)
					state.push(std::make_pair(curr.first->leftChild, false));
			}
		}

		void getNextLeavesOnly(){
			while(!state.empty() && state.top().second == false){
				std::pair< Node *, bool> curr = state.top();
				state.pop();
				if(curr.first->leftChild == nullptr && curr.first->rightChild == nullptr)
					state.push(std::make_pair(curr.first, true));
				if(curr.first->rightChild != nullptr)
					state.push(std::make_pair(curr.first->rightChild, false));
				if(curr.first->leftChild != nullptr)
					state.push(std::make_pair(curr.first->leftChild, false));
			}
		}

	public:
		
		void pred(const std::function<bool(const T&)> &pred_ = [](const T&)->bool{ return true; }){
			Pred = pred_;
			while(!state.empty())
				state.pop();
			state.push(std::make_pair(root_, false));
			getNext();
		}

		TreeIterator(Node *root_arg){
			root_ = root_arg;
			//pred();
		}

		TreeIterator(const TreeIterator &rhs){
			root_ = rhs.root_;
			state = rhs.state;
			traversal = rhs.traversal;
			Pred = rhs.Pred;
			getNext();
		}

		TreeIterator& operator=(const TreeIterator &rhs){
			if(this != &rhs){
				root_ = rhs.root_;
				state = rhs.state;
				traversal = rhs.traversal;
				Pred = rhs.Pred;		
				getNext();			
			}
		}

		void inorder(){
			if(root_ != nullptr){
				state.push(std::make_pair(root_, false));
				traversal = "inorder";
				getNextInorder();				
			}
		}

		void preorder(){
			if(root_ != nullptr){
				state.push(std::make_pair(root_, false));
				traversal = "preorder";
				getNextPreorder();				
			}
		}

		void postorder(){
			if(root_ != nullptr){
				state.push(std::make_pair(root_, false));
				traversal = "postorder";
				getNextPostorder();				
			}
		}

		void leavesOnly(){
			if(root_ != nullptr){
				state.push(std::make_pair(root_, false));
				traversal = "leavesOnly";
				getNextLeavesOnly();
			}
		}

		T& operator *(){
			return state.top().first->dataValue;
		}

		bool operator ==(const TreeIterator &it){
			return (state.empty() && it.state.empty()) ||
            	(!state.empty () && !it.state.empty() &&
                (state.top().first == it.state.top().first) && (state.top().second == it.state.top().second));
		}

		bool operator !=(const TreeIterator &it){
			return !(*this == it); 
		}

		TreeIterator& operator++(){
			state.pop();
			getNext();
		}

		void operator++(int){
			state.pop();
			getNext();
		}
	};

	TreeIterator begin(){
		TreeIterator it(root);
		return it;
	}

	TreeIterator end(){
		TreeIterator it(nullptr);
		return it;
	}


// Trees 4 homework tasks




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

	void subTreeSize(){
		subTreeSize(root);
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