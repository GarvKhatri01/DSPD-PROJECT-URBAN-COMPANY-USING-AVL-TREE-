#ifndef AVL_H
#define AVL_H

#include "common.h"

typedef struct avl_node_tag {
    int key;                        /* the ID (customer id, service id, ...) */
    void* data;                     /* points to the real record, we never copy it */
    int height;                     /* height of the subtree rooted here */
    struct avl_node_tag* left;
    struct avl_node_tag* right;
} AVLNode;

AVLNode* avlNewNode(int key, void* data);
int      avlHeight(AVLNode* node);
void     avlUpdateHeight(AVLNode* node);
int      avlBalance(AVLNode* node);
AVLNode* avlRotateRight(AVLNode* p);
AVLNode* avlRotateLeft(AVLNode* p);
AVLNode* avlInsert(AVLNode* root, int key, void* data);
void*    avlSearch(AVLNode* root, int key);
void     avlPrintKeys(AVLNode* root);
void avlFreeAll(AVLNode* root);

#endif