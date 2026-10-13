#include "tree.h"

#include <stdlib.h>
#include <stdio.h>

void insert_bst_rec(BSTNode **root, int data, float x, float y) {
    if (!*root)
    {
        BSTNode *newNode = malloc(sizeof(BSTNode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        newNode->size = 20;
        newNode->x = x;
        newNode->y = y;
        newNode->tx = x;
        newNode->ty = y;

        *root = newNode;
        return;
    }
    
    if (data < (*root)->data)
    {
        insert_bst_rec(&(*root)->left, data, (*root)->x, (*root)->y);
    }
    else if (data > (*root)->data)
    {
        insert_bst_rec(&(*root)->right, data, (*root)->x, (*root)->y);
    }

    return;
}

void insert_bst(BSTNode **root, int data) {
    insert_bst_rec(root, data, 300, 40);
}

void layout_bst(BSTNode *root, float x, float y, float offset) {
    if (!root)
    {
        return;
    }

    root->tx = x;
    root->ty = y;

    float nextY = y + 50;
    float nextXOffset = offset * 4;
    float nextOffset = offset / 2;
    
    layout_bst(root->left, x - nextXOffset, nextY, nextOffset);
    layout_bst(root->right, x + nextXOffset, nextY, nextOffset);

    return;
}

void remove_bst(BSTNode **root, int data) {
    if (*root == NULL) return;
    
    if (data > (*root)->data)
    {
        remove_bst(&(*root)->right, data);
        return;
    } 
    else if (data < (*root)->data)
    {
        remove_bst(&(*root)->left, data);
        return;
    }
    else // found data
    {
        // 2 children
        if ((*root)->left && (*root)->right) {

            // find smallest in left tree
            BSTNode *min = (*root)->right;
            while (min->left) {
                min = min->left;
            }
            
            // new root value
            (*root)->data = min->data;

            remove_bst(&(*root)->right, min->data);
        }
        else if (!(*root)->left && !(*root)->right) {
            free(*root);
            *root = NULL;
        }
        else
        {
            BSTNode *tmp = *root;
            *root = (*root)->right ? (*root)->right : (*root)->left;
            free(tmp);
        }
    }
}

void print_bst(BSTNode *root) {
    if (!root) return;
    print_bst(root->left);
    printf("%d ", root->data);
    print_bst(root->right);
}

void free_bst(BSTNode **root) {
    if (!*root) return;

    free_bst(&(*root)->left);
    free_bst(&(*root)->right);

    free(*root);
    *root = NULL;
    return;
}