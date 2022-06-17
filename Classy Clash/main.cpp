#include "raylib.h"
#include "raymath.h"

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

        if (Vector2Length(direction) != 0.0)
        {
            Vector2 movement = Vector2Normalize(direction);
            mapPos = Vector2Subtract(mapPos, Vector2Scale(movement, speed));
        }

        DrawTextureEx(map, mapPos, 0, 4.0, WHITE);

        Rectangle knightDest{knightPos.x, knightPos.y,
                             knightScale * (float)knight.width / 6.0f, knightScale * (float)knight.height};
        DrawTexturePro(knight, knightSource, knightDest, {0, 0}, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();

    UnloadTexture(map);
    UnloadTexture(knight);

    return 0;
}