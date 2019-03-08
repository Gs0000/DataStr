#include <iostream>
#include "LIFO.h"

using namespace std;

/****************************************************************
    行输入编辑
****************************************************************/
void Line_Edit()
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
    表达式求值
    使用两个工作栈，一个OPTR，寄存运算符，一个OPND，
	寄存操作数和运算结果
****************************************************************/

GI32 Precede(GCH8 a, GCH8 b);
GI32 Operate(GI32 a, GI32 b, GCH8 op);

void Calc_Expression()
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

	printf("仅支持+、-、*、/、()、=运算\n请输入表达式：");

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
				case 0: //优先级低
					Push_LIFO_Node(pOPTR, (GUC8*)&in, 1);
					in = getchar();
					break;
				case 1: //优先级相等，()的情况
					Delete_LIFO_Node(pOPTR, (GUC8*)&optr, 1);
					in = getchar();
					break;
				case 2: //优先级高，计算前面的数据
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
  运算符优先级
		+	-	*	/	(	）	=
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

/****************************************************************
hanoi塔问题
递归调用
****************************************************************/
void Hanoi_Move(GI32 i, GCH8 a, GCH8 b);

//三阶塔
void Hanoi_3(GI32 i, GCH8 a, GCH8 b, GCH8 c)
{
	if (i == 1)
		Hanoi_Move(1, a, c);
	else
	{
		Hanoi_3(i - 1, a, c, b);
		Hanoi_Move(i, a, c);
		Hanoi_3(i - 1, b, a, c);
	}
}

//四阶塔
void Hanoi_4(GI32 i, GI32 j, GCH8 a, GCH8 b, GCH8 c, GCH8 d)
{
	if (i > j)
	{
		Hanoi_4(i - j, j, a, c, d, b);
		Hanoi_3(j, a, c, d);
		Hanoi_4(i - j, j, b, a, c, d);
	}
	else
	{
		Hanoi_3(j, a, c, d);
	}

}

void Hanoi_Move(GI32 i, GCH8 a, GCH8 b)
{
	static int cnt = 1;
	printf("%d: %d -- %c -> %c\n", cnt++, i, a, b);
}

