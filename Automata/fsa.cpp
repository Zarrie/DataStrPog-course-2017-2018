#include "fsa.h"

int main(){

	DFSA d;
	d.load("fsa");
	//d.print(); // ok
	std::cout << d.traverse("acd") << std::endl;
	std::cout << d.traverse("bcdefghk") << std::endl;
	std::cout << d.traverse("qiweja") << std::endl;
	std::cout << d.traverse("q") << std::endl;
	std::cout << d.traverse("qaqe") << std::endl;
	std::cout << d.traverse("jk") << std::endl;
	//Passed tests!
	return 0;
}