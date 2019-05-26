#include <stdio.h>
#include <stdlib.h>

#define TElemType int

typedef struct BiTNode
{
    TElemType   data;
    struct BiTNode *lChild, *rChild;
    
} BiTNode, *BiTree;

BiTree CreateBiTree()
{
    // root
    BiTree *bt = (BiTree*)malloc(sizeof(BiTNode));
    (*bt)->data = 1;

    // left child
    (*bt)->lChild = (BiTNode*)malloc(sizeof(BiTNode));
    (*bt)->lChild->data = 2;
    // right child
    (*bt)->rChild = (BiTNode*)malloc(sizeof(BiTNode));
    (*bt)->rChild->data = 3;

    // null to leaf
    (*bt)->lChild->lChild = NULL;
    (*bt)->lChild->rChild = NULL;
    (*bt)->rChild->lChild = NULL;
    (*bt)->rChild->rChild = NULL;

    return *bt;
}

int main()
{
    BiTree tree = CreateBiTree();
    printf("left child data is: %d\n", tree->lChild->data);

    return 0;
}
