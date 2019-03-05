#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LIFO.h"

GI32 Create_LIFO(PtrLIFO *pLIFO)
{
	PtrLIFO ptr = NULL;
	
	if (pLIFO == NULL)
		return Gs_ERROR;
	
	ptr = (PtrLIFO)malloc(sizeof(StrLIFO));
	if (ptr == NULL)
		return Gs_FAILURE;
	
	ptr->pTop = ptr->pButtom = NULL;
	ptr->nodeCnt = 0;
	ptr->nodeSize = 0;
	pthread_mutex_init(&(ptr->mutex), NULL);
	*pLIFO = ptr;
	
	return Gs_SUCCESS;
}

GI32 Destroy_LIFO(PtrLIFO *pLIFO)
{
	PtrLIFO ptr = NULL;
	
	if (pLIFO == NULL || *pLIFO == NULL)
		return Gs_ERROR;
	
	free(*pLIFO);
	*pLIFO = NULL;
	
	return Gs_SUCCESS;
}

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

	return Gs_SUCCESS;
}

GI32 Clear_LIFO(PtrLIFO pLIFO)
{
    if (pLIFO == NULL)
        return Gs_ERROR;

    memset(pLIFO->pButtom, 0, pLIFO->nodeCnt*pLIFO->nodeSize);
    pLIFO->pTop = pLIFO->pButtom;

	return Gs_SUCCESS;
}

GI32 Push_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size)
{
	if (pLIFO == NULL || pNode == NULL || size > pLIFO->nodeSize)
		return Gs_ERROR;

	if (pLIFO->pTop - pLIFO->pButtom >= pLIFO->nodeCnt*pLIFO->nodeSize)
		return Gs_ERROR;

	memcpy(pLIFO->pTop, pNode, size);
	pLIFO->pTop += pLIFO->nodeSize;

	return Gs_SUCCESS;
}

GI32 Get_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size)
{
	if (pLIFO == NULL || pNode == NULL || size > pLIFO->nodeSize || pLIFO->pTop == pLIFO->pButtom)
		return Gs_ERROR;

    memcpy(pNode, pLIFO->pTop - pLIFO->nodeSize, size);

	return Gs_SUCCESS;
}

GI32 Delete_LIFO_Node(PtrLIFO pLIFO, GUC8 *pNode, GU32 size)
{
    if (pLIFO == NULL || pNode == NULL || size > pLIFO->nodeSize || pLIFO->pTop == pLIFO->pButtom)
	    return Gs_ERROR;

	pLIFO->pTop -= pLIFO->nodeSize;
	memcpy(pNode, pLIFO->pTop, size);

	return Gs_SUCCESS;
}





