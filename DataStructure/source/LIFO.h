#ifndef _LIFO_H_
#define _LIFO_H_

#include <pthread.h>
#include <semaphore.h>

#include "GsDEF.h"

#ifdef Gs_WIN
#pragma comment(lib, "pthreadVC2.lib")
#else
#pragma comment(lib, "libpthread.so");
#endif

typedef struct LIFONode_t {
	void *ptr;
	struct LIFONode_t *pPre;
	struct LIFONode_t *pNxt;
}StrLIFONode, *PtrLIFONode;

typedef struct LIFO_t {
	PtrLIFONode pTop;
	PtrLIFONode pButtom;
	GU32 nodeCnt;
	pthread_mutex_t mutex;
}StrLIFO, *PtrLIFO;

#ifdef __cplusplus
extern "C" {
#endif

	GI32 Create_LIFO(PtrLIFO *pLIFO); // 创建栈
	GI32 Destroy_LIFO(PtrLIFO *pLIFO); // 销毁栈
	GI32 Init_LIFO(PtrLIFO pLIFO, GU32 nodeCnt, GU32 nodeSize); // 初始化栈空间
	GI32 Clear_LIFO(PtrLIFO pLIFO); // 清空栈
	GI32 Get_LIFO_Node(PtrLIFO pLIFO, PtrLIFONode *pNode); // 获取栈顶节点
	GI32 Push_LIFO_Node(PtrLIFO pLIFO, PtrLIFONode pNode); // 插入栈顶节点
	GI32 Delete_LIFO_Top(PtrLIFO pLIFO); // 删除栈顶节点
	GI32 Remove_LIFO_Node(PtrLIFO pLIFO, PtrLIFONode pNode); // 删除栈中指定节点

#ifdef __cplusplus
}
#endif





#endif