#include "avl.h"

AVLNode* avlNewNode(int key, void* data) {
    AVLNode* ret_val;

    ret_val = (AVLNode*)malloc(sizeof(AVLNode));

    if (ret_val != NULL) {
        ret_val->key = key;
        ret_val->data = data;
        ret_val->height = 1;        /* a lone node has height 1 */
        ret_val->left = NULL;
        ret_val->right = NULL;
    }

    return ret_val;
}

int avlHeight(AVLNode* node) {
    int ret_val;

    ret_val = 0;                    /* empty tree has height 0 */
    if (node != NULL) {
        ret_val = node->height;
    }

    return ret_val;
}

void avlUpdateHeight(AVLNode* node) {
    int lh;
    int rh;

    lh = avlHeight(node->left);
    rh = avlHeight(node->right);

    if (lh > rh) {
        node->height = 1 + lh;
    } else {
        node->height = 1 + rh;
    }
}

int avlBalance(AVLNode* node) {
    int ret_val;

    ret_val = 0;
    if (node != NULL) {
        ret_val = avlHeight(node->left) - avlHeight(node->right);
    }

    return ret_val;
}

AVLNode* avlRotateRight(AVLNode* p) {
    AVLNode* q;

    q = p->left;
    p->left = q->right;             /* q's right subtree moves under p */
    q->right = p;                   /* p comes down, q goes up */

    avlUpdateHeight(p);             /* p is lower now, fix it first */
    avlUpdateHeight(q);

    return q;                       /* q is the new root of this part */
}

AVLNode* avlRotateLeft(AVLNode* p) {
    AVLNode* q;

    q = p->right;
    p->right = q->left;
    q->left = p;

    avlUpdateHeight(p);
    avlUpdateHeight(q);

    return q;
}

AVLNode* avlInsert(AVLNode* root, int key, void* data) {
    AVLNode* result;
    int bf;

    result = root;

    if (root == NULL) {
       result = avlNewNode(key, data);
    } else {
       
        if (key < root->key) {
            root->left = avlInsert(root->left, key, data);
        } else if (key > root->key) {
            root->right = avlInsert(root->right, key, data);
        }
        // they will not be same -already checked

        avlUpdateHeight(root);
        bf = avlBalance(root);

        if (bf > 1) {  
                                             //left height > right height
            if (avlBalance(root->left) < 0) {           // left is - '\'
                root->left = avlRotateLeft(root->left);
            }
            result = avlRotateRight(root);
        } 
        else if (bf < -1) {  //right > left  - '\\'
                                     
            if (avlBalance(root->right) > 0) {         //right - '/'
                root->right = avlRotateRight(root->right);
            }
            result = avlRotateLeft(root);
        }
    }

    return result;
}

void* avlSearch(AVLNode* root, int key) {
    void* result = NULL;
    AVLNode* current = root;
    boolean done = FALSE;

    while (current != NULL && done == FALSE) {

        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            result = current->data;    /* found it */
            done = TRUE;
        }
    }

    return result;
}

void avlPrintKeys(AVLNode* root) {

    if (root != NULL) {
        avlPrintKeys(root->left);
        printf("%d ", root->key);
        avlPrintKeys(root->right);
    }
}

void avlFreeAll(AVLNode* root) {

    if (root != NULL) {
        avlFreeAll(root->left);
        avlFreeAll(root->right);
        free(root->data);   //delete data it points       
        free(root);          // delete the node     
    }
}