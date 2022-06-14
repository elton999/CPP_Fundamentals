#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y < windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;

    if (data.runningTime >= data.updateTime)
    {
        if (data.frame > maxFrame)
            data.frame = 0;
        data.frame++;
        data.runningTime = 0;
    }
    data.rec.x = data.frame * data.rec.width;

    return data;
}

float updateBackground(int spriteWidth, float deltaTime, float posX, float velocity)
{
    posX -= velocity * deltaTime;
    if (posX <= -spriteWidth * 2)
        posX = 0;
    return posX;
}

void renderBackground(Texture2D sprite, float posX)
{
    Vector2 pos{posX, 0};
    Vector2 pos2{posX + sprite.width * 2, 0};
    DrawTextureEx(sprite, pos, 0, 2, WHITE);
    DrawTextureEx(sprite, pos2, 0, 2, WHITE);
}

int main(void)
{
    const int windowDimensions[2]{512, 380};

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae{10};
    AnimData nebulae[sizeOfNebulae]{};
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        AnimData nebData{
            {0, 0, nebula.width / 8, nebula.height / 8},
            {windowDimensions[0] + 300 * i, windowDimensions[1] - nebula.height / 8},
            0,
            1.0 / 12.0,
            0};
        nebulae[i] = nebData;
    }
    int nebVel{-600};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.runningTime = 0;
    scarfyData.updateTime = 1.0 / 12.0;

    const int gravity{1000};

    int velocity{0};
    int jumpVelocity{-600};

    bool isInAir{false};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt{GetFrameTime()};

        if (!isInAir)
            scarfyData = updateAnimData(scarfyData, dt, 5);

        isInAir = isOnGround(scarfyData, windowDimensions[1]);

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity * dt;

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        scarfyData.pos.y += velocity * dt;

        BeginDrawing();
        ClearBackground(WHITE);

        bgX = updateBackground(background.width, dt, bgX, 20);
        renderBackground(background, bgX);

        mgX = updateBackground(midground.width, dt, mgX, 40);
        renderBackground(midground, mgX);

        fgX = updateBackground(foreground.width, dt, fgX, 80);
        renderBackground(foreground, fgX);

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dt, 7);
            nebulae[i].pos.x += nebVel * dt;
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();

    return 0;
}