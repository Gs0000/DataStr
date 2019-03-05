#include <iostream>
#include "LIFO.h"

using namespace std;

/*栈应用 -- 行输入*/
void LineEdit()
{
	PtrLIFO pLIFO = NULL;
	GCH8 node;
	GCH8 in;

	Create_LIFO(&pLIFO);
	Init_LIFO(pLIFO, 128, 1);

	in = getchar();

	while (in != EOF)
	{
		switch (in)
		{
		case '#':
			Delete_LIFO_Node(pLIFO, (GUC8*)&node, 1);
			break;
		case '@':
			Clear_LIFO(pLIFO);
			break;
		default:
			Push_LIFO_Node(pLIFO, (GUC8*)&in, 1);
		}
		in = getchar();
	}
	printf("out: ");
	while (Delete_LIFO_Node(pLIFO, (GUC8*)&node, 1) == 0)
	{
		printf("%c", node);
	}
	printf("\n");

	Destroy_LIFO(&pLIFO);

	return;
}

/*表达式求值
  使用两个工作栈，一个OPTR，寄存运算符，一个OPND，寄存操作数和运算结果
  运算符
*/
