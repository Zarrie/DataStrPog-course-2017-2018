#include "SyntaxTree.h"


int main(){

	SyntaxTree tree;
	tree.parseExpression("((((5+3)*(4/2))+((3+1)*(1+1)))+(((1+3)*(2+4))+((3*4)*(1+1))))");
	std::cout << tree;

	return 0;
}