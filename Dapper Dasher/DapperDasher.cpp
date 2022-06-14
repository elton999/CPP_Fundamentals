#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main(void)
{
    const int windowWidth{800};
    const int windowHeight{450};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{
        {0, 0, nebula.width / 8, nebula.height / 8},
        {windowWidth, windowHeight - nebula.height / 8},
        0,
        1.0 / 12.0,
        0};

    int nebVel{-600};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.runningTime = 0;
    scarfyData.updateTime = 1.0 / 12.0;

    const int gravity{1000};

    int velocity{0};
    int jumpVelocity{-600};

    bool isInAir{false};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt{GetFrameTime()};
        nebData.runningTime += dt;

        if (!isInAir)
            scarfyData.runningTime += dt;

        if (scarfyData.runningTime >= scarfyData.updateTime)
        {
            if (scarfyData.frame > 5)
                scarfyData.frame = 0;
            scarfyData.frame++;
            scarfyData.runningTime = 0;
        }
        scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;

        if (nebData.runningTime >= nebData.updateTime)
        {
            if (nebData.frame > 7)
                nebData.frame = 0;
            nebData.frame++;
            nebData.runningTime = 0;
        }
        nebData.rec.x = nebData.frame * nebData.rec.width;

        isInAir = scarfyData.pos.y < windowHeight - scarfyData.rec.height;

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity * dt;

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        scarfyData.pos.y += velocity * dt;
        nebData.pos.x += nebVel * dt;

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    return 0;
}