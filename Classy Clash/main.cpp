#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main(void)
{
    const int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "RPG game");

    Character knight{};

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0, 4.0, WHITE);

        knight.setScreenPos(windowDimensions[0], windowDimensions[1]);
        knight.Tick(GetFrameTime());

        EndDrawing();
    }

    CloseWindow();

    return 0;
}