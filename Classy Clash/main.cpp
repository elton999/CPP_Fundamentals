#include "raylib.h"

int main(void)
{
    int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "RPG game");

    Texture2D tileSetSprite = LoadTexture("nature_tileset/tileset.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(tileSetSprite, {0, 0}, 0, 4.0, WHITE);
        EndDrawing();
    }

    CloseWindow();

    UnloadTexture(tileSetSprite);

    return 0;
}