#include "BiTree.h"
#include <stdio.h>
#include <stdlib.h>

void Traverse_BiTree_0(PtrBiTree pRoot)
{
    if (pRoot == NULL || pRoot->ptr == NULL)
        return;
    
    printf("%c\n", (GCH8)pRoot->ptr[0]);

    Traverse_BiTree_0(pRoot->pLChild);
    Traverse_BiTree_0(pRoot->pRChild);

}

void Traverse_BiTree_1(PtrBiTree pRoot)
{
    if (pRoot == NULL || pRoot->ptr == NULL)
        return;

    Traverse_BiTree_1(pRoot->pLChild);
    printf("%c\n", (GCH8)pRoot->ptr[0]);
    Traverse_BiTree_1(pRoot->pRChild);
}

GI32 Init_HuffmanTree(PtrHuffmanTree pRoot, GU32 nodeCnt)
{
    if (pRoot == NULL || nodeCnt == 0)
        return Gs_ERROR;

    pRoot->nodeCnt = 0;
    pRoot->pNode = (PtrHuffmanNode)calloc(nodeCnt, sizeof(StrHuffmanNode));
    if (pRoot->pNode == NULL)
        return Gs_FAILURE;

    pRoot->nodeCnt = nodeCnt;

    return Gs_SUCCESS;
}

GI32 Free_HuffmanTree(PtrHuffmanTree pRoot)
{
    if (pRoot == NULL || pRoot->pNode == NULL)
        return Gs_ERROR;

    free(pRoot->pNode);
    pRoot->pNode = NULL;
    pRoot->nodeCnt = 0;

    return Gs_SUCCESS;
}

void Select_Min_Node(PtrHuffmanTree pRoot, GI32 length, GI32 *pSerial_0, GI32 *pSerial_1)
{
    GI32 min_0, min_1;

    GI32 i;

    if (pRoot->nodeCnt == 0 || pRoot->nodeCnt < (GU32)length || length < 2)
        return;
    
    for (i = 1; i < length; i++)
    {
        if (pRoot->pNode[i].parent == 0)
        {
            min_0 = pRoot->pNode[i].weight;
            *pSerial_0 = i;
            i++;
            break;
        }
    }
    for (; i < length; i++)
    {
        if (pRoot->pNode[i].parent == 0)
        {
            if (min_0 > pRoot->pNode[i].weight)
            {
                min_1 = min_0;
                min_0 = pRoot->pNode[i].weight;
                *pSerial_1 = *pSerial_0;
                *pSerial_0 = i;
            }
            else
            {
                min_1 = pRoot->pNode[i].weight;
                *pSerial_1 = i;
            }
            i++;
            break;
        }
    }

    for (; i < length; i++)
    {
        if (pRoot->pNode[i].parent == 0)
        {
            if (min_0 > pRoot->pNode[i].weight)
            {
                min_1 = min_0;
                min_0 = pRoot->pNode[i].weight;
                *pSerial_1 = *pSerial_0;
                *pSerial_0 = i;
            }
            else if (min_1 > pRoot->pNode[i].weight)
            {
                min_1 = pRoot->pNode[i].weight;
                *pSerial_1 = i;
            }
        }
    }

    return;
}

GI32 Huffman_Code(PtrHuffmanTree pRoot, GCH8 **code, GI32 *weight, GI32 cnt)
{
    GI32 nodeCnt;
    GI32 s0, s1;
    GCH8 *pCode;
    GI32 start;
    GI32 parent;

    GI32 i, j;

    if (pRoot == NULL || cnt == 0)
        return Gs_ERROR;

    nodeCnt = cnt * 2 - 1;
    Init_HuffmanTree(pRoot, nodeCnt + 1);
    for (i = 1; i <= cnt; i++)
    {
        pRoot->pNode[i].weight = weight[i - 1];
    }

    for (i = cnt + 1; i <= nodeCnt; i++)
    {
        Select_Min_Node(pRoot, i, &s0, &s1);
        pRoot->pNode[s0].parent = i;
        pRoot->pNode[s1].parent = i;
        pRoot->pNode[i].lChild = s0;
        pRoot->pNode[i].rChild = s1;
        pRoot->pNode[i].weight = pRoot->pNode[s0].weight + pRoot->pNode[s1].weight;
    }

    pCode = (GCH8*)calloc(cnt, 1);

    for (i = 1; i <= cnt; i++)
    {
        start = cnt - 1;
        for (j = i, parent = pRoot->pNode[i].parent; parent != 0; j = parent, parent = pRoot->pNode[parent].parent)
        {
            if (j == pRoot->pNode[parent].lChild)
                pCode[--start] = '0';
            else
                pCode[--start] = '1';
        }
        code[i - 1] = (GCH8*)malloc((cnt - start) * sizeof(GCH8));
        memcpy(code[i - 1], pCode + start, cnt - start);
    }

    Free_HuffmanTree(pRoot);

    return Gs_SUCCESS;
}