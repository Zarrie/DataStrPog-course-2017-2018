#include "AST.h"

int main(){

	AST tree;
	tree.parseExpression("(((5+3)*(4+4))+((3+1)*(1+1)))");
	std::cout << tree;

	return 0;
}