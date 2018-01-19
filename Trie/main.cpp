#include "dictionary.h"

void dictionaryINSERTtest(){
	dictionary d;
	d.insert("banana");
	d.insert("cocoa");
	d.insert("coconut");
	std::cout << d.find("coconut");
	std::cout << d.find("coconuts");
	std::cout << std::endl;

	d.printTree();
}

void dictionaryREMOVEtest(){
	dictionary d;
	d.insert("banana");
	d.insert("cocoa");
	d.insert("coconut");
	std::cout << d.find("coconut");
	std::cout << d.find("coconuts");
	d.remove("coconut");
	std::cout << d.find("coconut");
	std::cout << std::endl;
	d.remove("badWordGiven");
}

void dictionaryCOPYandASSIGNEMENTtest(){
	dictionary d;
	d.insert("banana");
	d.insert("cocoa");
	d.insert("coconut");
	std::cout << d.find("coconut");
	dictionary d1 = d;
	std::cout << d1.find("coconut");
	d.remove("coconut");
	std::cout << d1.find("coconut");
	std::cout << d.find("coconut");
	std::cout << std::endl;
}

int main(){
	//dictionaryINSERTtest();
	//dictionaryREMOVEtest();
	//dictionaryCOPYandASSIGNEMENTtest();
	return 0;
}