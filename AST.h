#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <functional>

#include <iostream>
#include <iomanip>
#include <exception>

class AST{
private:
	class Node{
	public:
		Node* leftChild;
		Node* rightChild;
		char dataValue;

		static unsigned	int maxID;
		unsigned int id;

		Node(const char &_dataValue) : leftChild(nullptr), rightChild(nullptr), dataValue(_dataValue) {
			id = maxID;
			maxID++;
		}

		unsigned int inline getId() const{
			return id;
		}
	};

	Node *root;

	bool isLeaf(const Node *curr) const{
		return curr->leftChild == nullptr && curr->rightChild == nullptr;
	}

	bool isTerminal(char c){
		return c >= '0' && c <= '9';
	}

	Node* evolve(const AST &leftSubTree, const AST &rightSubTree){

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
	AST() : root(nullptr){

	}

	AST(const AST& rhs){

	}

	unsigned int findRoot(const std::string &str) const{
		unsigned int brackets = 0;
		for(unsigned int i = 0 ; i < str.length() ; ++i){
			if(str[i] == '(')
				brackets++;
			if(str[i] == ')'){
				brackets--;
				if(brackets == 1)
					return i;
			}
			throw logic_error("Something went terribly wrong!");
		}
	}

	Node* subTree(const std::string &str){
		if(str.length() == 1)
			return new Node(str[0]);
		if(str.length() == 3){
			subRoot = new Node(str[1]);
			subRoot->leftChild = new Node(str[0]);
			subRoot->rightChild = new Node(str[2]);
		}
		else {
			int 
			subRoot = new Node(str[findRoot(str)]);

		}
	}

	AST parseExpression(const std::string &str){
		if(str.length() == 1){
			root = new Node(str[0]);
			return *this;
		}
		if(str.length() == 3){
			root = new Node(str[1]);
			root->leftChild = new Node(str[0]);
			root->rightChild = new Node(str[2]);
			return *this;
		}
	}

	friend std::ostream& operator << (std::ostream &out, const AST &tree){
		out << "digraph G {" << std::endl;
		printDotty(out, tree.root);
		out << "}" << std::endl;
		return out;
	}
	
	~AST(){

	}
};

unsigned int AST::Node::maxID = 0;