#include <iostream>
#include "TestAPI.h"
using namespace std;

int main(int argc, char **argv) 
{
	int a = -1;
	if(argc == 2)
		a = atoi(argv[1]);
	switch (a)
	{
	case 0:
		Line_Edit(); break;	
	case 1:
		Calc_Expression(); break;
	case 2:
		Hanoi_3(3, 'A', 'B', 'C'); break;		
	case 3:
        Queen(0); break;	
	default:
		break;
	}

	
	return 0;
}
