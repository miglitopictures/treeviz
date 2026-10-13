#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

struct BSTNode
{
    int data;
    
    float x;
    float y;
    float tx;
    float ty;
    float radius;
    
    struct BSTNode *left;
    struct BSTNode *right;
};

typedef struct BSTNode BSTNode;

void insert_bst_rec(BSTNode **root, int data, float x, float y) {
    if (!*root)
    {
        BSTNode *newNode = malloc(sizeof(BSTNode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        newNode->radius = 20;
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

void remove_bst(BSTNode **root, int data, int mode) {
    if (*root == NULL) return;
    
    if (data > (*root)->data)
    {
        remove_bst(&(*root)->right, data, mode);
        return;
    } 
    else if (data < (*root)->data)
    {
        remove_bst(&(*root)->left, data, mode);
        return;
    }
    else // found data
    {
        // 2 children
        if ((*root)->left && (*root)->right) {

            switch (mode)
            {
                case 0: {   // by merge
                    BSTNode *tmp = *root;
                    BSTNode *originalLeftBranch = (*root)->left;
                    
                    *root = (*root)->right;
        
                    // find smallest in left tree
                    BSTNode *min = *root;
                    while (min->left) {
                        min = min->left;
                    }
        
                    min->left = originalLeftBranch;
        
                    free(tmp);
                    break;
                }
                default: { // by splice
                    BSTNode **link = &(*root)->right;
                    // find smallest in left tree
                    while ((*link)->left) {
                        link = &(*link)->left;
                    }
    
                    BSTNode *min = *link;
                    *link = min->right;
    
                    min->left = (*root)->left;
                    min->right = (*root)->right;
                    
                    // new root value
                    free(*root);
                    *root = min;
                    break;
                }
            }


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

void update_bst(BSTNode **root, int removal_mode) {
    if (!*root) return;

    (*root)->x = Lerp((*root)->x,(*root)->tx,0.1);
    (*root)->y = Lerp((*root)->y,(*root)->ty,0.1);

    float distance = Vector2Distance(GetMousePosition(), (Vector2){(*root)->x, (*root)->y});
    if (distance <= (*root)->radius)
    {   // HOVER
        (*root)->radius = 25;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            remove_bst(root, (*root)->data, removal_mode);
            return;
        }
    }
    else
    {
        
        (*root)->radius = 20;
    }

    update_bst(&(*root)->left, removal_mode);
    update_bst(&(*root)->right, removal_mode);
}

void draw_bst(BSTNode *root) {
    if (!root) return;
    
    if (root->left)
    DrawLineEx((Vector2){root->x, root->y}, (Vector2){root->left->x, root->left->y}, root->radius/4, BLACK);
    if (root->right)
    DrawLineEx((Vector2){root->x, root->y}, (Vector2){root->right->x, root->right->y}, root->radius/4, BLACK);
    
    DrawCircle(root->x, root->y, root->radius, RED);
    const char *dataStr = TextFormat("%d", root->data);
    float width = MeasureText(dataStr, root->radius);
    DrawText(dataStr, root->x - width/2, root->y - root->radius/2, root->radius, BLACK);
    
    draw_bst(root->left);
    draw_bst(root->right);
}

void insert_starting_nodes(BSTNode **tree) {
    free_bst(tree);
    insert_bst(tree, 50);
    insert_bst(tree, 20);
    insert_bst(tree, 70);
    insert_bst(tree, 10);
    insert_bst(tree, 60);
    insert_bst(tree, 55);
    insert_bst(tree, 6);
    insert_bst(tree, 15);
    insert_bst(tree, 25);
    insert_bst(tree, 45);
    insert_bst(tree, 23);
    insert_bst(tree, 12);
    insert_bst(tree, 65);
}


typedef struct State {
    int removal_mode;
    float selected_value;
} State;


int main() {
    /* Setup */

    State app = {0};
    app.removal_mode = 0;
    app.selected_value = 50;

    BSTNode *tree = NULL;

    // starting tree (demo)
    insert_starting_nodes(&tree);

    InitWindow(600,600, "Trees");
    SetTargetFPS(30);

    bool removalDropdownEditMode = false;


    while (!WindowShouldClose())
    {
        /* Update */
        update_bst(&tree, app.removal_mode);
        layout_bst(tree, 300, 40, 20);
        /* Draw */
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_bst(tree);

            // interface
            if (GuiDropdownBox((Rectangle) {40, 40, 100, 40}, "Merge;Splice", &app.removal_mode, removalDropdownEditMode))
            {
                removalDropdownEditMode = !removalDropdownEditMode;
            }


            if (GuiButton((Rectangle) {40, GetScreenHeight() - 200, 100, 40},"default tree"))
            {
                insert_starting_nodes(&tree);
            }

            if (GuiButton((Rectangle) {40, GetScreenHeight() - 150, 100, 40},"Clear tree"))
            {
                free_bst(&tree);
            }

            GuiSliderBar((Rectangle) {40, GetScreenHeight() - 50, GetScreenWidth() - 80, 20},"0", "99", &app.selected_value, 0, 99);

            if (GuiButton((Rectangle) {40, GetScreenHeight() - 100, 100, 40},TextFormat("Add %.0f", floor(app.selected_value))))
            {
                insert_bst(&tree, floor(app.selected_value));
            }

        EndDrawing();
    }

    CloseWindow();
    
    free_bst(&tree);
    
    return 0;
}
