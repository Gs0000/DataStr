#include <iostream>
#include "ByLIFO.h"
using namespace std;


int main(int argc, char **argv) 
{
	int a = -1;
	if(argc == 2)
		a = atoi(argv[1]);
	switch (a)
	{
	case 0:
		LineEdit();
		break;
	case 1:
		CalcExpression();
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}

	
	return 0;
}
