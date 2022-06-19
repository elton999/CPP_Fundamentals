#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"

int main(void)
{
    const int windowDimensions[2]{384, 384};

    InitWindow(windowDimensions[0], windowDimensions[1], "RPG game");

    Character knight{windowDimensions[0], windowDimensions[1]};

    Enemy goblin{
        Vector2{0, 0},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    goblin.setTarget(&knight);

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
        DrawTextureEx(map, mapPos, 0, scale, WHITE);

        for (auto prop : props)
            prop.Render(knight.getWorldPos());

        float dT = GetFrameTime();

        goblin.tick(dT);

        knight.tick(dT);

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