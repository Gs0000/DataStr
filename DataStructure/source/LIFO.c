#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LIFO.h"

GI32 Create_LIFO(PtrLIFO *pLIFO)
{
	PtrLIFO ptr = NULL;
	
	if (pLIFO == NULL)
		return G_ERROR;
	
	ptr = (PtrLIFO)malloc(sizeof(StrLIFO));
	if (ptr == NULL)
		return G_FAILURE;
	
	ptr->pTop = ptr->pButtom = NULL;
	ptr->nodeCnt = 0;
	pthread_init_mutex(&(ptr->mutex), NULL);
	*pLIFO = ptr;
	
	return G_SUCCESS;
}

GI32 Destroy_LIFO(PtrLIFO *pLIFO)
{
	PtrLIFO ptr = NULL;
	
	if (pLIFO == NULL || *pLIFO == NULL)
		return G_ERROR;
	
	ptr = *pLIFO;
	while (ptr->pTop)
	{
		
	}
	
	
	
	free(ptr);
	ptr = NULL;
	
	
	return G_SUCCESS;
}

