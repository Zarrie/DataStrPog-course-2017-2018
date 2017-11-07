#pragma once

#include <fstream>
#include <string>
#include <iostream>

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

	bool isDigit(const char ch) const{
		return ch >= '0' && ch <= '9';
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

	void clear(Node *& curr){
		if(curr == nullptr)
			return;
		Node *&leftSubTree = curr->leftChild;
		Node *&rightSubTree = curr->rightChild;
		delete curr;
		clear(leftSubTree);
		clear(rightSubTree);
	}

public:
	AST() : root(nullptr) {}

	AST(const AST& rhs) = delete;
	AST& operator=(const AST& rhs) = delete;

	Node* EvolveSubTree(std::string &str){
		if(str.length() == 0)
			return nullptr;
		//Current expression is digit terminal so we construct one node tree with the value of str[0]
		if(isDigit(str[0])){
			char terminal = str[0];
			str.erase(str.begin(), str.begin() + 1);
			return new Node(terminal);
		}
		//Current expression is in the form (expression operator expression) so we recursively parse it
		else{
			//Read '(' from ( expr op expr )
			str.erase(str.begin(), str.begin() + 1);
			//Read left SubtTree expression
			Node *leftSubTree = EvolveSubTree(str);
			//Read operator
			Node *subTreeRoot = new Node(str[0]);
			//Read 'operator' from (expr operator expr)
			str.erase(str.begin(), str.begin() + 1);
			//Read right subTree expression
			Node *rightSubTree = EvolveSubTree(str);
			//Read ')' from (expr op expr )
			str.erase(str.begin(), str.begin() + 1);
			//Connect the root with left and right subtree
			subTreeRoot->leftChild = leftSubTree;
			subTreeRoot->rightChild = rightSubTree;
			return subTreeRoot;
		}
	}

	void parseExpression(const std::string &str){
		std::string copy = str;
		root = EvolveSubTree(copy);
	}

	friend std::ostream& operator << (std::ostream &out, const AST &tree){
		out << "digraph G {" << std::endl;
		printDotty(out, tree.root);
		out << "}" << std::endl;
		return out;
	}
	
	~AST(){
		//clear(root);
	}
};

unsigned int AST::Node::maxID = 0;
