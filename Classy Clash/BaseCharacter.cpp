#include "BaseCharacter.h"
#include "raymath.h"
BaseCharacter::BaseCharacter() {}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    texture = idle;
    if (Vector2LengthSqr(velocity) != 0.0)
    {
        Vector2 movement = Vector2Normalize(velocity);
        worldPos = Vector2Add(worldPos, Vector2Scale(movement, speed));
        rightLeft = velocity.x < 0.f ? -1 : 1;
        texture = run;
    }

    velocity = {};

    Rectangle source{frame * width, 0, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0, WHITE);
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        scale * width,
        scale * height};
}

void BaseCharacter::undoMovement() { worldPos = worldPosLastFrame; }