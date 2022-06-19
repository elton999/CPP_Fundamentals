#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrames;
    height = texture.height;

    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive())
        return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
        target->takeDamage(damagePerSecond * deltaTime);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
