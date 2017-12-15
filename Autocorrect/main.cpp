#include "autocorrect.h"
#include <fstream>

void insertTestDict(){
	Dictionary d;
	d.insert("potato");
	d.insert("potatoes");
	d.insert("");
	d.insert("tomatoes");
	d.insert("tom");
	d.insert("");
	d.insert("tomato");
	d.insert("tom");
	d.insert("tompson");
	d.insert("potate");
	d.insert("pirate");
	d.remove("tom");
	std::cout << d;
}

void generateTestDict(){
	Dictionary d;
	d.insert("potato");
	d.insert("potatoes");
	d.insert("");
	d.insert("tomatoes");
	d.insert("");
	d.insert("tomato");
	d.insert("tom");
	d.insert("potade");
	d.insert("potase");
	d.insert("potasere");

	for( auto it : d.suggestions("potsto", 2))
		std::cout << it << " ";
	std::cout << "\n";
}

bool isValid(const std::string &word){
	for(int i = 0 ; i < word.length() ; ++i)
		if(word[i] < 'a' || word[i] > 'z')
			return false;
	return true;;
}

void bigDataTest(){
	std::ifstream words("dictionary", std::ios::in);
	std::string curr;
	Dictionary d;
	while(!words.eof()){
		words >> curr;
		if(isValid(curr))
			d.insert(curr);
	}
	std::string word;
	while(true){
		std::cin >> word;
		if(word == "0") break;
		for( auto it : d.suggestions(word, 5))
			std::cout << it << " ";
		std::cout << "\n";		
	}

	/*for(int i = 0 ; i < 1000 ; ++i){
		words >> curr;
		if(isValid(curr))
			d.insert(curr);
	}*/
	//std::cout << d;
}

int main(){
	//insertTestDict();
	//generateTestDict();
	bigDataTest();

	return 0;
}