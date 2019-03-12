#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FIFO.h"

GI32 Init_FIFO(PtrFIFO pFIFO, GU32 nodeCnt, GU32 nodeSize)
{
    PtrQueueNode pNode;
    int i;

    if (pFIFO == NULL || nodeCnt < 2 || !nodeSize)
        return Gs_ERROR;

    pFIFO->pBuffer = (GUC8 *)malloc(nodeCnt*nodeSize);
    if (pFIFO->pBuffer == NULL)
        return Gs_FAILURE;

    pFIFO->pFront = (PtrQueueNode)malloc(sizeof(StrQueueNode));
    pFIFO->pFront->ptr = pFIFO->pBuffer;
    pFIFO->pFront->pNext = NULL;
    pFIFO->pRear = pFIFO->pFront;
    for (i = 1; i < nodeCnt; i++)
    {
        pNode = (PtrQueueNode)malloc(sizeof(StrQueueNode));
        pNode->ptr = pFIFO->pBuffer + i*nodeSize;
        pNode->pNext = NULL;
        pFIFO->pRear->pNext = pNode;
        pFIFO->pRear = pNode;
    }
    pFIFO->pCur = pFIFO->pFront;
    pFIFO->nodeCnt = nodeCnt;
    pFIFO->nodeSize = nodeSize;
    pFIFO->dataCnt = 0;
    pthread_mutex_init(&pFIFO->mutex, NULL);

	return Gs_SUCCESS;
}

GI32 Free_FIFO(PtrFIFO pFIFO)
{

    PtrQueueNode pNode;

    if (pFIFO == NULL)
        return Gs_ERROR;

    while (pFIFO->pFront)
    {
        pNode = pFIFO->pFront->pNext;
        free(pFIFO->pFront);
        pFIFO->pFront = pNode;
    }
    pFIFO->pRear = pFIFO->pCur = NULL;

    if (pFIFO->pBuffer)
    {
        free(pFIFO->pBuffer);
        pFIFO->pBuffer = NULL;
    }
 
    pFIFO->nodeCnt = 0;
    pFIFO->nodeSize = 0;
    pFIFO->dataCnt = 0;
    pthread_mutex_destroy(&pFIFO->mutex);

    return Gs_SUCCESS;
}

GI32 FIFO_Length(PtrFIFO pFIFO)
{
    if (pFIFO == NULL)
        return Gs_ERROR;

    return pFIFO->dataCnt;
}

GI32 Clear_FIFO(PtrFIFO pFIFO)
{
    if (pFIFO == NULL)
        return Gs_ERROR;

    if (pFIFO->pBuffer)
    {
        memset(pFIFO->pBuffer, 0, pFIFO->nodeCnt*pFIFO->nodeSize);
    }
    pFIFO->pCur = pFIFO->pFront;
    pFIFO->dataCnt = 0;

    return Gs_SUCCESS;
}

GI32 Get_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size)
{
    if (pFIFO == NULL || pNode == NULL || size > pFIFO->nodeSize)
        return Gs_ERROR;

    if (pFIFO->pFront == pFIFO->pCur)
        return Gs_FAILURE;

    memcpy(pNode, pFIFO->pFront, size);

    return Gs_SUCCESS;
}

GI32 Push_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size)
{
    if (pFIFO == NULL || pNode == NULL || size > pFIFO->nodeSize)
        return Gs_ERROR;

    if (pFIFO->pCur == NULL)
        return Gs_FAILURE;

    memcpy(pFIFO->pCur, pNode, size);
    pFIFO->pCur = pFIFO->pCur->pNext;
    pFIFO->dataCnt ++;

    return Gs_SUCCESS;
}

GI32 Pull_FIFO_Node(PtrFIFO pFIFO, GUC8 *pNode, GU32 size)
{
    if (pFIFO == NULL || pNode == NULL || size > pFIFO->nodeSize)
        return Gs_ERROR;

    if (pFIFO->pFront == pFIFO->pCur)
        return Gs_FAILURE;

    memcpy(pNode, pFIFO->pFront, size);
    pFIFO->pRear->pNext = pFIFO->pFront;
    pFIFO->pRear = pFIFO->pFront;
    pFIFO->pFront = pFIFO->pFront->pNext;
    pFIFO->pRear->pNext = NULL;
    pFIFO->dataCnt --;

    return Gs_SUCCESS;
}