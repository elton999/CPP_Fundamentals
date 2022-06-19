#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;

    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

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
}