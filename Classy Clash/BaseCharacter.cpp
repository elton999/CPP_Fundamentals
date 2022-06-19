#include "BaseCharacter.h"
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

    Rectangle source{frame * width, 0, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0, WHITE);
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        scale * width,
        scale * height};
}

void BaseCharacter::undoMovement() { worldPos = worldPosLastFrame; }