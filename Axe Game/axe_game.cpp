#include "raylib.h"

int main(void)
{
    int width = 350;
    int height = 200;

    InitWindow(width, height, "Axe Game");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}