#include <iostream>
#include "LIFO.h"

using namespace std;

/****************************************************************
    ������༭
****************************************************************/
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

/****************************************************************
    ���ʽ��ֵ
    ʹ����������ջ��һ��OPTR���Ĵ��������һ��OPND��
	�Ĵ��������������
****************************************************************/

GI32 Precede(GCH8 a, GCH8 b);
GI32 Operate(GI32 a, GI32 b, GCH8 op);

void CalcExpression()
{
	PtrLIFO pOPTR = NULL;
	PtrLIFO pOPND = NULL;
	GCH8 in;
	GUC8 ngtvFlg = 0;
	GI32 value = 0;
	GCH8 optr = 0;
	GI32 a, b;

	Create_LIFO(&pOPTR);
	Init_LIFO(pOPTR, 128, 1);
	Create_LIFO(&pOPND);
	Init_LIFO(pOPND, 128, sizeof(GI32));

	printf("��֧��+��-��*��/��()��=����\n��������ʽ��");

	in = getchar();
	while (in != EOF && optr!= '=')
	{
		if (in == '-' && ngtvFlg == 0)
		{
			in = getchar();
			value = 0;
			while (in >= '0' && in <= '9')
			{
				value = value*10 + in - '0';
				in = getchar();
			}
			value *= -1;
			Push_LIFO_Node(pOPND, (GUC8*)&value, 4);
			ngtvFlg = 1;
		}
		else if (in >= '0' && in <= '9')
		{
			value = 0;
			while (in >= '0' && in <= '9')
			{
				value = value * 10 + in - '0';
				in = getchar();
			}
			Push_LIFO_Node(pOPND, (GUC8*)&value, 4);
			ngtvFlg = 1;
		}
		else if (in == '+' || in == '-' || in == '*' || in == '/' || in == '(' || in == ')' || in == '=')
		{
			if (Get_LIFO_Node(pOPTR, (GUC8*)&optr, 1) == Gs_SUCCESS)
			{
				switch (Precede(optr, in))
				{
				case 0: //���ȼ���
					Push_LIFO_Node(pOPTR, (GUC8*)&in, 1);
					in = getchar();
					break;
				case 1: //���ȼ���ȣ�()�����
					Delete_LIFO_Node(pOPTR, (GUC8*)&optr, 1);
					in = getchar();
					break;
				case 2: //���ȼ��ߣ�����ǰ�������
					Delete_LIFO_Node(pOPTR, (GUC8*)&optr, 1);
					Delete_LIFO_Node(pOPND, (GUC8*)&b, 4);
					Delete_LIFO_Node(pOPND, (GUC8*)&a, 4);
					value = Operate(a, b, optr);
					Push_LIFO_Node(pOPND, (GUC8*)&value, 4);
				}
			}
			else
			{
				Push_LIFO_Node(pOPTR, (GUC8*)&in, 1);
				in = getchar();
			}
				
			ngtvFlg = 0;
		}
		else
			in = getchar();

		Get_LIFO_Node(pOPTR, (GUC8*)&optr, 1);
	}

	Get_LIFO_Node(pOPND, (GUC8*)&value, 1);
	printf("res = %d\n", value);

	return;
}

/*
  ��������ȼ�
		+	-	*	/	(	��	=
	+   >	>	<	<	<	<	>
	-	>	>	<	<	<	<	>
	*	>	>	>	>	<	<	>
	/	>	>	>	>	<	<	>
	(	<	<	<	<	<	=	
	)	>	>	>	>		>	>
	=	<	<	<	<	<		=
*/
GI32 Precede(GCH8 a, GCH8 b)
{
	GI32 ret = 0;
	GI32 theta_0 = 0, theta_1 = 0;

	switch (a)
	{
	case '+':
	case '-':theta_0 = 4; break;
	case '*':
	case '/':theta_0 = 6; break;
	case '(':theta_0 = 1; break;
	case ')':theta_0 = 8; break;
	case '=':theta_0 = 0; break;
	default:
		return Gs_ERROR;
	}
	switch (b)
	{
	case '+':
	case '-':theta_1 = 3; break;
	case '*':
	case '/':theta_1 = 5; break;
	case '(':theta_1 = 7; break;
	case ')':theta_1 = 1; break;
	case '=':theta_1 = 0; break;
	default :
		return Gs_ERROR;
	}

	if (a == '(' && b == '#' || 
		a == ')' && b == '(' )
	{
		return Gs_ERROR;
	}

	if (theta_0 > theta_1)
		ret = 2;
	else if (theta_0 == theta_1)
		ret = 1;
	else
		ret = 0;

	return ret;
}

GI32 Operate(GI32 a, GI32 b, GCH8 op)
{
	switch (op)
	{
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': 
		if (b == 0)
			return Gs_ERROR;
		else
			return a / b;
	default:
		return Gs_ERROR;
	}
}