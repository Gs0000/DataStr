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

    GI32 Init_FIFO(PtrFIFO pFIFO, GU32 nodeCnt, GU32 nodeSize); // ��ʼ�����пռ�
	GI32 Free_FIFO(PtrFIFO pFIFO); // �ͷŶ��пռ�
    GI32 FIFO_Length(PtrFIFO pFIFO); // ��ȡ�������ݳ���

	/*���Զ��н��ж��̶߳�ȡ�Ͷ��߳��޸�ʱ�����º�������ǰ����߳�����pFIFO->mutex*/
	GI32 Clear_FIFO(PtrFIFO pFIFO); // ��ն��пռ�
	GI32 Get_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size); // ��ȡ����ͷ�ڵ�����
	GI32 Push_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size); // д����нڵ�����
    GI32 Pull_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size); // �Ƴ�����ͷ�ڵ�����

#ifdef __cplusplus
}
#endif


#endif