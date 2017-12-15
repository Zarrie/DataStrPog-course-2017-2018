#pragma once

#include <iostream>
#include <vector>
#include <string>

#define ALPHABET_SIZE 26
#define MAX_NEIGHBOURS 9

class Dictionary{
private:
	class node{
	private:
		bool final;
		node *transitions[ALPHABET_SIZE];

	public:
		static unsigned	int maxID;
		unsigned int id;

		unsigned int inline getId() const{
			return id;
		}

		node(bool state = false) : final(state){
			id = maxID;
			maxID++;
			for(int i = 0 ; i < ALPHABET_SIZE ; ++i)
				transitions[i] = nullptr;
		}

		node(const node &) = delete;
		node &operator=(const node &) = delete;

		inline bool state() const{
			return final;
		}

		inline void setState(bool newState){
			final = newState;
		}

		inline node *operator[] (const char ch){
			return transitions[ch - 'a'];
		}

		inline const node *operator[] (const char ch) const{
			return transitions[ch - 'a'];
		}
		
		bool setNext(const char ch, node *child){
			if(transitions[ch - 'a'] == nullptr){
				transitions[ch - 'a'] = child;
				return true;
			}
			else return false;
		}

		~node(){
			for(unsigned int i = 0 ; i < ALPHABET_SIZE ; ++i)
				delete transitions[i];
		}
	};

	size_t numberOfWords;

	node *root;

	static char neighbours[ALPHABET_SIZE][MAX_NEIGHBOURS];

public:

	Dictionary() : root(new node), numberOfWords(0){

	}

	bool find(const std::string &word) const{
		if(word.length() == 0 || root == nullptr)
			return false;
		node *curr = root;
		for(unsigned int i = 0 ; i < word.length() ; ++i){
			curr = (*curr)[word[i]];
			if(curr == nullptr)
				return false;
		}
		return curr->state();
	}

	bool insert(const std::string &word){
		if(word.length() == 0)
			return false;
		else{
			node *curr = root;
			unsigned int i = 0;
			while((*curr)[word[i]] != nullptr && i < word.length()){
				curr = (*curr)[word[i++]];
			}
			if(i == word.length()){
				curr->setState(true);
				numberOfWords++;
				return true;
			}
			curr->setNext(word[i], new node);
			for(unsigned int j = i ; j < word.length() ; ++j){
				curr->setNext(word[j], new node);
				curr = (*curr)[word[j]];
			}
			curr->setState(true);
			numberOfWords++;
			return true;
		}
	}

	void remove(const std::string &word){
		node *curr = root;
		unsigned int i = 0;
		while((*curr)[word[i]] != nullptr && i < word.length())
			curr = (*curr)[word[i++]];
		if(curr != nullptr && i >= word.length())
			curr->setState(false);
	}

	void generate(node *curr, const std::string &substr, const char ch, std::vector < std::string >& result, size_t numberOfWords = 5){
		if(result.size() == numberOfWords)
			return;
		else if(curr->state()){
			result.push_back(substr);
			return;
		}
		else{
			unsigned int pos = ch - 'a';
			for(int i = 0 ; i < MAX_NEIGHBOURS ; ++i){
				node *next = (*curr)[neighbours[pos][i]];
				if(next != nullptr){
					generate(next, substr + neighbours[pos][i], neighbours[pos][i], result, numberOfWords);
					if(result.size() >= numberOfWords)
						return;
				}
			}
		}
	}

	std::vector < std::string > suggestions(const std::string &word, size_t numberOfWords = 5){
		if(word.length() == 0 || root == nullptr)
			std::vector < std::string >();
		node *curr = root;
		std::vector < std::string > result;
		for(unsigned int i = 0 ; i < word.length() ; ++i){
			if((*curr)[word[i]] == nullptr){
				generate(curr, word.substr(0, i), word[i], result, numberOfWords);
				return result;
			}
			curr = (*curr)[word[i]];
		}
		result.push_back(word);
		generate(curr, word, word[word.length() - 1], result, numberOfWords);
		return result;
	}

	// --------------------------------- Utility ---------------------------------

	bool null(){
		return root == nullptr;
	}

	static void printDotty(std::ostream &out, node *curr){
		if(curr == nullptr){
			return;
		}
		for(int i = 0 ; i < ALPHABET_SIZE ; ++i){
			node *curr_ = (*curr)['a'+i];
			if(curr_){
				if(curr_->state())
					out << curr_->getId() << "[color = \"red\"]" << ";" << std::endl;
				out << curr->getId() << "->" << curr_->getId() << "[label = " << (char)('a' + i) << "];" << std::endl;
				printDotty(out, curr_);
			}
		}
	}

	friend std::ostream& operator << (std::ostream &out, const Dictionary &dict){
		out << "digraph G {" << std::endl;
		printDotty(out, dict.root);
		out << "}" << std::endl;
		return out;
	}

	// --------------------------------- Utility ---------------------------------

	~Dictionary(){

	}
};

unsigned int Dictionary::node::maxID = 0;

char Dictionary::neighbours[ALPHABET_SIZE][MAX_NEIGHBOURS] = {
	{'a','q','s','d','w','z','x','e','c'},
	{'b','v','n','f','g','h','m','d','j'},
	{'c','x','v','d','s','f','g','b','a'},
	{'d','s','f','w','e','r','x','c','v'},
	{'e','w','r','d','f','s','a','q','t'},
	{'f','d','g','e','r','t','c','v','b'},
	{'g','f','h','e','r','t','v','b','n'},
	{'h','g','j','t','y','u','b','n','m'},
	{'i','u','o','j','k','l','y','p','l'},
	{'j','h','k','y','u','i','n','b','m'},
	{'k','j','l','i','u','o','m','n','b'},
	{'l','k','o','p','j','i','u','h','m'},
	{'m','n','j','k','l','b','h','v','u'},
	{'n','b','m','j','h','k','v','g','l'},
	{'o','i','p','l','k','j','y','g','h'},
	{'p','o','l','i','k','j','u','y','m'},
	{'q','a','w','s','z','e','d','x','f'},
	{'r','e','t','f','d','g','y','q','a'},
	{'s','a','d','q','w','e','z','x','c'},
	{'t','r','y','f','g','h','u','e','d'},
	{'u','y','i','j','h','k','o','p','r'},
	{'v','c','b','d','f','g','h','n','x'},
	{'w','q','e','s','a','d','f','g','z'},
	{'x','s','z','c','a','f','q','w','e'},
	{'y','t','u','g','h','j','k','l','p'},
	{'z','a','s','d','c','v','f','q','e'}
};