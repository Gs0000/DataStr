#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LIFO.h"

GI32 Init_LIFO(PtrLIFO pLIFO, GU32 nodeCnt, GU32 nodeSize)
{
    if (pLIFO == NULL || !nodeCnt || !nodeSize)
        return Gs_ERROR;

    pLIFO->pButtom = (GUC8 *)malloc(nodeCnt*nodeSize);
    if (pLIFO->pButtom == NULL)
        return Gs_FAILURE;
    pLIFO->pTop = pLIFO->pButtom;
    pLIFO->nodeCnt = nodeCnt;
    pLIFO->nodeSize = nodeSize;
    pLIFO->dataCnt = 0;
    pthread_mutex_init(&pLIFO->mutex, NULL);

    return Gs_SUCCESS;
}

GI32 Free_LIFO(PtrLIFO pLIFO)
{
	if (pLIFO == NULL)
		return Gs_ERROR;

    if (pLIFO->pButtom)
        free(pLIFO->pButtom);
    pthread_mutex_destroy(&pLIFO->mutex);

	return Gs_SUCCESS;
}

GI32 LIFO_Length(PtrLIFO pLIFO)
{
    if (pLIFO == NULL)
        return Gs_ERROR;

    return pLIFO->dataCnt;
}

GI32 Clear_LIFO(PtrLIFO pLIFO)
{
    if (pLIFO == NULL)
        return Gs_ERROR;

    memset(pLIFO->pButtom, 0, pLIFO->nodeCnt*pLIFO->nodeSize);
    pLIFO->pTop = pLIFO->pButtom;

	return Gs_SUCCESS;
}

GI32 Get_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size)
{
    if (pLIFO == NULL || pNode == NULL || size > pLIFO->nodeSize)
        return Gs_ERROR;

    if (pLIFO->pTop == pLIFO->pButtom)
        return Gs_FAILURE;

    memcpy(pNode, pLIFO->pTop - pLIFO->nodeSize, size);

    return Gs_SUCCESS;
}

GI32 Push_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size)
{
	if (pLIFO == NULL || pNode == NULL || size > pLIFO->nodeSize)
		return Gs_ERROR;

    if (pLIFO->pTop - pLIFO->pButtom >= pLIFO->nodeCnt*pLIFO->nodeSize)
        return Gs_FAILURE;

	memcpy(pLIFO->pTop, pNode, size);
	pLIFO->pTop += pLIFO->nodeSize;
    pLIFO->dataCnt ++;

	return Gs_SUCCESS;
}

GI32 Pull_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size)
{
	if (pLIFO == NULL || pNode == NULL || size > pLIFO->nodeSize)
		return Gs_ERROR;

    if (pLIFO->pTop == pLIFO->pButtom)
        return Gs_FAILURE;

	pLIFO->pTop -= pLIFO->nodeSize;
	memcpy(pNode, pLIFO->pTop, size);
    pLIFO->dataCnt --;

	return Gs_SUCCESS;
}





