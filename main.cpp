#include "AST.h"

int main(){

	AST tree;
	tree.parseExpression("5+3");
	std::cout << tree;

	return 0;
}