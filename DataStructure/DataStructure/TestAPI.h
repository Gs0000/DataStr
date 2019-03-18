#pragma once
#ifndef _TESTAPI_H_
#define _TESTAPI_H_
#include "GsDEF.h"

#ifdef __cplusplus
extern "C" {
#endif

/*行输入编辑*/
void Line_Edit();

/*表达式求值*/
void Calc_Expression();

/*hanoi塔问题*/
void Hanoi_3(GI32 i, GCH8 a, GCH8 b, GCH8 c);
void Hanoi_4(GI32 i, GI32 j, GCH8 a, GCH8 b, GCH8 c, GCH8 d);

/*八皇后问题*/
void Queen(GI32 row);

/*KMP算法解决字符串中查找子串问题*/
void KMP_Locate();

/*二叉树问题*/
void Test_BiTree();

#ifdef __cplusplus
}
#endif

#endif