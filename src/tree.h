#ifndef TREE_H
#define TREE_H


struct BSTNode
{
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
};

typedef struct BSTNode BSTNode;

void insert_bst(BSTNode **root, int data);
void print_bst(BSTNode *root);
void free_bst(BSTNode **root);

#endif