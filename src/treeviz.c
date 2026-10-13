#include <math.h>

#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "tree.h"

void update_bst(BSTNode **root) {
    if (!*root) return;
    float distance = Vector2Distance(GetMousePosition(), (Vector2){(*root)->x, (*root)->y});
    if (distance <= (*root)->size)
    {   // HOVER
        (*root)->size = 25;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            remove_bst(root, (*root)->data);
            return;
        }
    }
    else
    {
        
        (*root)->size = 20;
    }

    update_bst(&(*root)->left);
    update_bst(&(*root)->right);
}

void draw_bst(BSTNode *root) {
    if (!root) return;
    
    if (root->left)
    DrawLineEx((Vector2){root->x, root->y}, (Vector2){root->left->x, root->left->y}, root->size/4, BLACK);
    if (root->right)
    DrawLineEx((Vector2){root->x, root->y}, (Vector2){root->right->x, root->right->y}, root->size/4, BLACK);
    
    DrawCircle(root->x, root->y, root->size, RED);
    const char *dataStr = TextFormat("%d", root->data);
    float width = MeasureText(dataStr, root->size);
    DrawText(dataStr, root->x - width/2, root->y - root->size/2, root->size, BLACK);
    
    draw_bst(root->left);
    draw_bst(root->right);
}



int main() {

    BSTNode *tree = NULL;

    insert_bst(&tree, 50);
    insert_bst(&tree, 20);
    insert_bst(&tree, 70);
    insert_bst(&tree, 10);
    insert_bst(&tree, 60);
    insert_bst(&tree, 55);
    insert_bst(&tree, 6);
    insert_bst(&tree, 15);
    insert_bst(&tree, 25);
    insert_bst(&tree, 45);
    insert_bst(&tree, 23);
    insert_bst(&tree, 12);
    insert_bst(&tree, 65);

    InitWindow(600,600, "Trees");
    SetTargetFPS(30);

    float selectedValue = 50;
    while (!WindowShouldClose())
    {
        update_bst(&tree);
        /* Render */
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_bst(tree);

            // interface
            if (GuiButton((Rectangle) {40, GetScreenHeight() - 160, 100, 40},"Clear tree"))
            {
                free_bst(&tree);
            }

            GuiSliderBar((Rectangle) {40, GetScreenHeight() - 50, GetScreenWidth() - 80, 20},"0", "99", &selectedValue, 0, 99);
            if (GuiButton((Rectangle) {40, GetScreenHeight() - 100, 100, 40},TextFormat("Add %.0f", floor(selectedValue))))
            {
                insert_bst(&tree, floor(selectedValue));
            }

        EndDrawing();
    }

    CloseWindow();
    
    free_bst(&tree);
    
    return 0;
}
