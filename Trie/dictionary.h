#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <exception>

#include <iostream>

using word = std::string;

class dictionary{
private:

	class node{
	public:
		bool final;
		std::unordered_map <char, node *> transitions;

		node() : final(false){}
	};

	node *root;

	void allWords(const node *currNode, word currWord, std::vector<word> &result) const{
		if(currNode == nullptr)
			return;
		if(currNode->final)
			result.push_back(currWord);
		for(auto it : currNode->transitions)
			allWords(it.second, currWord + it.first, result);
	}

	void removeDictionary(node *&currNode){
		if(currNode == nullptr)
			return;
		for(auto it : currNode->transitions)
			removeDictionary(it.second);
		delete currNode;
	}

public:
	dictionary() : root(new node()) {}

	dictionary(const dictionary &rhs) {
		std::vector<word> wordsToInsert;
		allWords(rhs.root, std::string(), wordsToInsert);
		for(auto it : wordsToInsert)
			this->insert(it);
	}

	dictionary& operator=(const dictionary &rhs){
		if(this == &rhs)
			return *this;
		std::vector<word> wordsToInsert;
		allWords(rhs.root, std::string(), wordsToInsert);
		for(auto it : wordsToInsert)
			this->insert(it);
		return *this;
	}

	void insert(const word &newWord){
		if(newWord.empty())
			return;
		node *currNode = root;
		uint wordPos = 0;
		while(wordPos < newWord.length() && currNode->transitions.find(newWord[wordPos]) != currNode->transitions.end()){
			currNode = currNode->transitions.at(newWord[wordPos]);
			wordPos++;
		}
		while(wordPos < newWord.length()){
			currNode->transitions[newWord[wordPos]] = new node();
			currNode = currNode->transitions[newWord[wordPos]];
			++wordPos;
		}
		currNode->final = true;
	}

	void remove(const word &removeWord){
		node *currNode = root;
		uint wordPos = 0;
		while(wordPos < removeWord.length() && currNode->transitions.find(removeWord[wordPos]) != currNode->transitions.end()){
			currNode = currNode->transitions.at(removeWord[wordPos]);
			++wordPos;
		}
		if(wordPos < removeWord.length())
			throw std::invalid_argument("Given word for removal is not in the Trie!");
		else
			currNode->final = false;
	}

	bool find(const word &searchingWord) const{
		if(searchingWord.empty())
			return false;
		uint wordPos = 0;
		node *currNode = root;
		while(wordPos < searchingWord.length() && currNode->transitions.find(searchingWord[wordPos]) != currNode->transitions.end()){
			currNode = currNode->transitions.at(searchingWord[wordPos]);
			++wordPos;
		}
		if(wordPos < searchingWord.length())
			return false;
		else
			return currNode->final;
	}

	// utility functions
	void print(const node *currNode, word currWord) const{
		if(!currNode)
			return;
		if(currNode->final)
			std::cout << currWord << std::endl;
		for(auto it : currNode->transitions)
			print(it.second, currWord + it.first);
	}

	void printTree() const{
		print(root, std::string());
	}

	~dictionary(){
		//removeDictionary(root);
	}

};
