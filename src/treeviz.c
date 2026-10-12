#include <math.h>

#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "tree.h"

void animate_bst(BSTNode *root) {
    if (!root) return;
    // float distance = Vector2Distance
}

void draw_bst(BSTNode *root, float x, float y, float size) {
    if (!root) return;
    
    float nextY = y + 50;
    float nextLeftX  = x - size * 4;
    float nextRightX = x + size * 4;
    
    if (root->left)
    DrawLineEx((Vector2){x, y}, (Vector2){nextLeftX, nextY}, 5, BLACK);
    if (root->right)
    DrawLineEx((Vector2){x, y}, (Vector2){nextRightX, nextY}, 5, BLACK);
    const char *dataStr = TextFormat("%d", root->data);
    float width = MeasureText(dataStr, 20);
    DrawCircle(x, y, 20, RED);
    DrawText(dataStr, x - width/2, y - 10, 20, BLACK);
    
    draw_bst(root->left, nextLeftX, nextY, size/2);
    draw_bst(root->right, nextRightX, nextY, size/2);
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
    SetTargetFPS(60);

    float selectedValue = 50;
    while (!WindowShouldClose())
    {
        /* Render */
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_bst(tree, GetScreenWidth()/2, 50, 20);

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

