#include "raylib.h"

int main(void)
{
    const int windowWidth{800};
    const int windowHeight{450};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    const int gravity{1};

    int velocity{0};
    int jumpVelocity{-21};

    bool isInAir{false};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        isInAir = scarfyPos.y < windowHeight - scarfyRec.height;

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity;

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        scarfyPos.y += velocity;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();

    return 0;
}