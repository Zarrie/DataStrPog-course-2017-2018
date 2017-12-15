#include "autocorrect.h"

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

int main(){
	insertTestDict();
	generateTestDict();

	return 0;
}