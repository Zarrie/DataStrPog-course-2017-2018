#include <string>
#include <iostream>
#include <fstream>
#include <exception>

#define final '$'
#define alphabetSize 256

using word = std::string;

class DFSA{
private:
	char* transitions;
	char* edgeLabels; // Since we have a single rule for every nonterminating symbol A := aB, then we can keep each transition A --a--> B in a one-D array
	//char initialState;

	void connectToFinal(const char from, const char label){
		edgeLabels[from] = label;
		transitions[from] = final;
	}

	void connectToNonFinal(const char from, const char to, const char label){
		edgeLabels[from] = label;
		transitions[from] = to;
	}

	char findInitState(const char edge) const{
		for(int i = 1 ; i < alphabetSize ; ++i){
			if(edgeLabels[i] == edge)
				return i;
		}
		return 0;
	}

public:
	DFSA(){
		transitions = new char[alphabetSize];
		edgeLabels = new char[alphabetSize];
		for(int i = 0 ; i < alphabetSize ; ++i){
			transitions[i] = 0;
			edgeLabels[i] = 0;
		}
	}

	void load(const std::string &filename){
		std::ifstream file(filename);
		if(!file.is_open())
			throw std::invalid_argument("Invalid filename!");
		std::string from, special, to;
		//file >> initialState;
		while(file >> from){
			file >> special; // ignoring the := symbol from the rules representation
			file >> to;
			if(to.length() == 1){
				connectToFinal(from[0], to[0]);
			}
			else if(to.length() == 2){
				connectToNonFinal(from[0], to[1], to[0]);
			}
			else
				throw std::invalid_argument("Invalid rule in the grammar!");
		}
	}

	bool traverse(const word &currWord) const{
		if(currWord.length() == 0)
			return false;
		char currState = findInitState(currWord[0]);
		if(currState == 0)
			return false;
		currState = transitions[currState];
		uint currWordPos = 1;
		while(currWordPos < currWord.length() && edgeLabels[currState] == currWord[currWordPos]){
			currState = transitions[currState];
			++currWordPos;
		}
		if(currWordPos == currWord.length())
			return currState == final;
		else
			return false;
	}
};