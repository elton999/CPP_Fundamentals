#include "raylib.h"

int main(void)
{
    int width{800};
    int height{450};

    InitWindow(width, height, "Dapper Dasher");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}