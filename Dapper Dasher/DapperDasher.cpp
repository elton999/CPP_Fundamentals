#include "raylib.h"

int main(void)
{
    const int windowWidth{800};
    const int windowHeight{450};

    const int gravity{1};

    const int width{50};
    const int height{80};
    int posY{windowHeight - height};

    int velocity{0};
    int jumpVelocity{-21};

    bool isInAir{false};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        isInAir = posY < windowHeight - height;

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity;

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}