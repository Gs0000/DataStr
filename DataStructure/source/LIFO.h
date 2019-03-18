#pragma once
#ifndef _LIFO_H_
#define _LIFO_H_

/****************************************************************


****************************************************************/

#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC
#endif
#include <pthread.h>
#include <semaphore.h>

#include "GsDEF.h"

#ifdef Gs_WIN
#pragma comment(lib, "pthreadVC2.lib")
#else
#pragma comment(lib, "libpthread.so");
#endif

typedef struct LIFO_t {
	GUC8 *pTop;
	GUC8 *pButtom;
	GU32 nodeCnt;
	GU32 nodeSize;
    GI32 dataCnt;
	pthread_mutex_t mutex;
}StrLIFO, *PtrLIFO;

#ifdef __cplusplus
extern "C" {
#endif

    /*需要提前申请pLIFO内存空间*/
    GI32 Init_LIFO(PtrLIFO pLIFO, GU32 nodeCnt, GU32 nodeSize); // 初始化栈空间
	GI32 Free_LIFO(PtrLIFO pLIFO); // 释放栈空间
    GI32 LIFO_Length(PtrLIFO pLIFO); // 获取栈数据深度 

	/*当对栈进行多线程读取和多线程修改时，以下函数调用前需加线程锁，pLIFO->mutex*/
	GI32 Clear_LIFO(PtrLIFO pLIFO); // 清空栈
    GI32 Get_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size); // 获取栈顶节点
	GI32 Push_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size); // 插入栈顶节点
	GI32 Pull_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size); // 删除栈顶节点

#ifdef __cplusplus
}
#endif

#endif