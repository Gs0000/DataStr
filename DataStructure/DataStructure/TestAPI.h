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

/*遍历二叉树*/
void Test_BiTree();

/*Huffman编码*/
void Test_HuffmanCode(GI32 cnt);

/*CPU占用问题*/
void CPU_Cost();

#ifdef __cplusplus
}
#endif

#endif