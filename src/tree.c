#include "tree.h"

#include <stdlib.h>
#include <stdio.h>

void insert_bst(BSTNode **root, int data) {
    if (!*root)
    {
        BSTNode *newNode = malloc(sizeof(BSTNode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        *root = newNode;
        return;
    }

    
    if (data < (*root)->data)
    {
        insert_bst(&(*root)->left, data);
    }
    else if (data > (*root)->data)
    {
        insert_bst(&(*root)->right, data);
    }

    return;
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