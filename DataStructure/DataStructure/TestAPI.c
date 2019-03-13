#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LIFO.h"

/****************************************************************
    行输入编辑
****************************************************************/
void Line_Edit()
{
    PtrLIFO pLIFO = NULL;
	GCH8 node;
	GCH8 in;

    pLIFO = (PtrLIFO)malloc(sizeof(StrLIFO));
	Init_LIFO(pLIFO, 128, 1);

	in = getchar();

	while (in != EOF)
	{
		switch (in)
		{
		case '#':
			Pull_LIFO_Node(pLIFO, (GUC8*)&node, 1);
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
	while (Pull_LIFO_Node(pLIFO, (GUC8*)&node, 1) == 0)
	{
		printf("%c", node);
	}
	printf("\n");

	Free_LIFO(pLIFO);
    free(pLIFO);

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

    pOPTR = (PtrLIFO)malloc(sizeof(StrLIFO));
	Init_LIFO(pOPTR, 128, 1);
    pOPND = (PtrLIFO)malloc(sizeof(StrLIFO));
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
					Pull_LIFO_Node(pOPTR, (GUC8*)&optr, 1);
					in = getchar();
					break;
				case 2: //优先级高，计算前面的数据
					Pull_LIFO_Node(pOPTR, (GUC8*)&optr, 1);
					Pull_LIFO_Node(pOPND, (GUC8*)&b, 4);
					Pull_LIFO_Node(pOPND, (GUC8*)&a, 4);
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

    Free_LIFO(pOPTR);
    free(pOPTR);
    Free_LIFO(pOPND);
    free(pOPND);

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

/****************************************************************
八皇后问题
回溯递归调用
****************************************************************/
GUC8 Test_Queen[8] = {0};

GI32 Point_OK(GI32 row, GI32 col);

void Queen(GI32 row)
{
    static int cnt = 0;
    int i;

    if (row == 8)
    {
        cnt ++;
    }
    else
    {
        for (i = 0; i < 8; i++)
        {
            if (Point_OK(row, i))
            {
                Test_Queen[row] = i+1;
                Queen(row + 1);
                Test_Queen[row] = 0;
            }
        }
    }

    if (row == 0)
        printf("Problem of eight queen has %d solutions\n", cnt);

    return;
}

GI32 Point_OK(GI32 row, GI32 col)
{
    GUC8 setPoint;
    int i;
    for (i = 0; i < row; i++)
    {
        setPoint = Test_Queen[i] - 1;
        if (setPoint == col)
            return 0;
        if (i - setPoint == row - col)
            return 0;
        if (i + setPoint == row + col)
            return 0;
    }
    return 1;
}

/****************************************************************
KMP算法解决字符串中查找子串问题
子串最大长度为127
****************************************************************/
GI32* KMP_Next(GCH8 *pT);

void KMP_Locate()
{
    GCH8 S[256] = { 0 };
    GCH8 T[128] = { 0 };
    GI32 *pNext = NULL;
    GI32 sLen = 0;
    GI32 tLen = 0;
    GI32 cnt = 0;
    GI32 i, j;

    printf("input search string: ");
    gets_s(S, 255);
    printf("input search target: ");
    gets_s(T, 127);

    pNext = KMP_Next(T);
    if (!pNext)
        return ;

    sLen = (GI32)strlen(S);
    tLen = (GI32)strlen(T);

    for (i = 0, j = 0; i < sLen;)
    {
        if (j == tLen)
        {
            cnt ++;
            j = 0;
        }
        else if(j == -1 || S[i] == T[j])
        {
            i ++;
            j ++;
        }
        else
        {
            j = pNext[j];
        }
    }

    if (j == tLen)
        cnt++;

    printf("search count : %d\n", cnt);

    free(pNext);

    return ;
}

GI32* KMP_Next(GCH8 *pT)
{
    GI32 length = 0;
    GI32 *pNext = NULL;
    GI32 i, j;

    length = (GI32)strlen(pT);
    if (length ==0 || length > 127)
        return NULL;

    pNext = (GI32 *)malloc(length*sizeof(GI32));
    pNext[0] = -1;
    j = -1;
    for (i = 0; i < length - 1;)
    {
        if (j == -1 || pT[i] == pT[j])
            pNext[++i] = ++j;
        else
            j = pNext[j];
    }

    return pNext;
}