#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        winWidth / 2.0f - 4.f * (0.5f * width),
        winHeight / 2.0f - 4.f * (0.5f * height)};
}

void Character::Tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    texture = idle;
    if (Vector2Length(direction) != 0.0)
    {
        Vector2 movement = Vector2Normalize(direction);
        worldPos = Vector2Add(worldPos, Vector2Scale(movement, speed));
        rightLeft = direction.x < 0.f ? -1 : 1;
        texture = run;
    }

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    Rectangle source{frame * width, 0, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0, WHITE);
}
