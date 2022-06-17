#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }

private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right, -1 : facing left
    int rightLeft{1};
    // Animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
};

int main(void)
{
    const int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "RPG game");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        windowDimensions[0] / 2.0f - (0.5f * (float)knight.width / 6.0f),
        windowDimensions[1] / 2.0f - (0.5f * (float)knight.height)};
    Rectangle knightSource{0, 0, (float)knight.width / 6.0f, (float)knight.height};
    float knightScale = 4.0;

    // 1 : facing right, -1 : facing left
    int rightLeft{1};

    // Animation variables
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        knight = knight_idle;
        if (Vector2Length(direction) != 0.0)
        {
            Vector2 movement = Vector2Normalize(direction);
            mapPos = Vector2Subtract(mapPos, Vector2Scale(movement, speed));
            rightLeft = direction.x < 0.f ? -1 : 1;
            knight = knight_run;
        }

        DrawTextureEx(map, mapPos, 0, 4.0, WHITE);

        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames)
                frame = 0;
        }

        knightSource.width = (float)knight.width / 6.0f * (float)rightLeft;
        knightSource.x = knightSource.width * frame;
        Rectangle knightDest{knightPos.x, knightPos.y,
                             knightScale * (float)knight.width / 6.0f, knightScale * (float)knight.height};
        DrawTexturePro(knight, knightSource, knightDest, Vector2{}, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();

    UnloadTexture(map);
    UnloadTexture(knight_run);
    UnloadTexture(knight_idle);

    return 0;
}