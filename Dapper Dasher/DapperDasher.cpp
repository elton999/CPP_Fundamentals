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

    const int gravity{1000};

    int velocity{0};
    int jumpVelocity{-600};

    bool isInAir{false};

    int frame{0};
    float updateTime{1.0 / 12.0};
    float runningTime{0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt{GetFrameTime()};
        runningTime += dt;

        if (runningTime >= updateTime)
        {
            if (frame > 5)
                frame = 0;
            frame++;
            runningTime = 0;
        }

        scarfyRec.x = frame * scarfyRec.width;

        BeginDrawing();
        ClearBackground(WHITE);

        isInAir = scarfyPos.y < windowHeight - scarfyRec.height;

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity * dt;

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        scarfyPos.y += velocity * dt;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();

    return 0;
}