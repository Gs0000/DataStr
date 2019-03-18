#pragma once
#ifndef _BITREE_H_
#define _BITREE_H_

#include "GsDEF.h"

typedef struct BiTree_t {
    GUC8 *ptr;
    struct BiTree_t *pLChild;
    struct BiTree_t *pRChild;
}StrBiTree, *PtrBiTree;

#ifdef __cplusplus
extern "C" {
#endif

    GI32 Init_BiTree(PtrBiTree pRoot);
    GI32 Free_BiTree(PtrBiTree pRoot);

    void Traverse_BiTree_0(PtrBiTree pRoot);
    void Traverse_BiTree_1(PtrBiTree pRoot);


    /*huffman tree*/

    /*red&black tree*/


#ifdef __cplusplus
}
#endif

#endif