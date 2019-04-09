#pragma once
#ifndef _BITREE_H_
#define _BITREE_H_

#include "GsDEF.h"

typedef struct BiTree_t {
    GUC8 *ptr;
    struct BiTree_t *pLChild;
    struct BiTree_t *pRChild;
}StrBiTree, *PtrBiTree;

typedef struct HuffmanNode_t {
    GI32 weight;
    GI32 parent;
    GI32 lChild;
    GI32 rChild;
}StrHuffmanNode, *PtrHuffmanNode;

typedef struct HuffmanTree_t {
    PtrHuffmanNode pNode;
    GU32 nodeCnt;
}StrHuffmanTree, *PtrHuffmanTree;

#ifdef __cplusplus
extern "C" {
#endif

    void Traverse_BiTree_0(PtrBiTree pRoot);
    void Traverse_BiTree_1(PtrBiTree pRoot);


    /*huffman tree*/

    GI32 Init_HuffmanTree(PtrHuffmanTree pRoot, GU32 nodeCnt);
    GI32 Free_HuffmanTree(PtrHuffmanTree pRoot);
    GI32 Huffman_Code(PtrHuffmanTree pRoot, GCH8 **code, GI32 *weight, GI32 cnt);

    /*red&black tree*/


#ifdef __cplusplus
}
#endif

#endif