#pragma once
#ifndef _BYLIFO_H_
#define _BYLIFO_H_
#include "GsDEF.h"

/*行输入编辑*/
void Line_Edit();
/*表达式求值*/
void Calc_Expression();
/*hanoi塔问题*/
void Hanoi_3(GI32 i, GCH8 a, GCH8 b, GCH8 c);
void Hanoi_4(GI32 i, GI32 j, GCH8 a, GCH8 b, GCH8 c, GCH8 d);

#endif