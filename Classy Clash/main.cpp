#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main(void)
{
    const int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "RPG game");

    Character knight{windowDimensions[0], windowDimensions[1]};

    Prop props[2]{
        Prop{
            LoadTexture("nature_tileset/Rock.png"),
            Vector2{300, 300}},
        Prop{
            LoadTexture("nature_tileset/Log.png"),
            Vector2{600, 200}}};

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

        for (auto prop : props)
            prop.Render(knight.getWorldPos());

        knight.Tick(GetFrameTime());

        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > map.width * scale ||
            knight.getWorldPos().y + windowDimensions[1] > map.height * scale)
            knight.undoMovement();

        for (auto prop : props)
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
                knight.undoMovement();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}