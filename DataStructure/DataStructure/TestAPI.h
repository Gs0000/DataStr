#pragma once
#ifndef _TESTAPI_H_
#define _TESTAPI_H_
#include "GsDEF.h"

#ifdef __cplusplus
extern "C" {
#endif

/*������༭*/
void Line_Edit();

/*����ʽ��ֵ*/
void Calc_Expression();

/*hanoi������*/
void Hanoi_3(GI32 i, GCH8 a, GCH8 b, GCH8 c);
void Hanoi_4(GI32 i, GI32 j, GCH8 a, GCH8 b, GCH8 c, GCH8 d);

/*�˻ʺ�����*/
void Queen(GI32 row);

/*KMP�㷨����ַ����в����Ӵ�����*/
void KMP_Locate();

/*����������*/
void Test_BiTree();

#ifdef __cplusplus
}
#endif

#endif