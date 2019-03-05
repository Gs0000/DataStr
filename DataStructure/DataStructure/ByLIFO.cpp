#include <iostream>
#include "LIFO.h"

using namespace std;

/*ջӦ�� -- ������*/
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

/*���ʽ��ֵ
  ʹ����������ջ��һ��OPTR���Ĵ��������һ��OPND���Ĵ��������������
  �����
*/
