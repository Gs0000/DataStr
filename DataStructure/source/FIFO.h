#pragma once
#ifndef _FIFO_H_
#define _FIFO_H_

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

typedef struct QueueNode_t {
	GUC8 *ptr;
	struct QueueNode_t *pNext;
}StrQueueNode, *PtrQueueNode;

typedef struct Queue_t {
	GUC8 *pBuffer;
	StrQueueNode *pFront;
	StrQueueNode *pRear;
    StrQueueNode *pCur;
	GU32 nodeCnt;
	GU32 nodeSize;
    GI32 dataCnt;
	pthread_mutex_t mutex;
}StrFIFO, *PtrFIFO;

#ifdef __cplusplus
extern "C" {
#endif

    GI32 Init_FIFO(PtrFIFO pFIFO, GU32 nodeCnt, GU32 nodeSize); // 初始化队列空间
	GI32 Free_FIFO(PtrFIFO pFIFO); // 释放队列空间
    GI32 FIFO_Length(PtrFIFO pFIFO); // 获取队列数据长度

	/*当对队列进行多线程读取和多线程修改时，以下函数调用前需加线程锁，pFIFO->mutex*/
	GI32 Clear_FIFO(PtrFIFO pFIFO); // 清空队列空间
	GI32 Get_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size); // 获取队列头节点数据
	GI32 Push_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size); // 写入队列节点数据
    GI32 Pull_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size); // 移出队列头节点数据

#ifdef __cplusplus
}
#endif


#endif