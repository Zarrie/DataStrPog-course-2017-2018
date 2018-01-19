#include <string>
#include <iostream>

#define graphsize 7

const char G[graphsize][graphsize] ={0, 'a', 'c', 0, 'b', 0, 0,
									 0,  0,  'd', 0,  0,  0, 0,
									 0, 'd',  0, 'd', 0, 'a',0,
									 0, 'd', 'b', 0,  0,  0,'c',
									 0,  0,  'a', 0,  0,  0, 0,
									 0,  0,   0, 'd', 0,  0, 0,
									 0,  0,   0,  0,  0,  0, 0};

int read(const std::string &word, const uint root){
	if(word.empty())
		return 1;
	int result = 0;
	for(int i = 0 ; i < graphsize ; ++i){
		if(G[root][i] == word[0]){
			result += read(word.substr(1), i);
		}
	}
	return result;
}

uint allPaths(const std::string &word){
	int result = 0;
	for(int i = 0 ; i < graphsize ; ++i)
		result += read(word, i);
	return result;
}

int main(){
	std::cout << allPaths("bad") << std::endl;

	return 0;
}