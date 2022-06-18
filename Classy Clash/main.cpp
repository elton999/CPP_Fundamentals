#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main(void)
{
    const int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "RPG game");

    Character knight{windowDimensions[0], windowDimensions[1]};

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    const float scale{4.0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0, 4.0, WHITE);

        knight.Tick(GetFrameTime());

        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > map.width * scale ||
            knight.getWorldPos().y + windowDimensions[1] > map.height * scale)
            knight.undoMovement();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}