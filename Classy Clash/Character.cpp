#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth),
                                                    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::takeDamage(float demage)
{
    health -= demage;
    if (health <= 0.f)
        setAlive(false);
}

void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin = {weapon.width * scale, weapon.height * scale};
    Vector2 offset = {25.f, 55.f};
    weaponCollisionRec = {
        getScreenPos().x + offset.x - weapon.width * scale,
        getScreenPos().y + offset.y - weapon.height * scale,
        weapon.width * scale,
        weapon.height * scale};

    rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0;
    if (rightLeft > 0.f)
    {
        origin.x = 0.f;
        offset.x = 35.f;
        weaponCollisionRec.x += weapon.width * scale;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0;
    }

    Rectangle source{0, 0, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};

    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
    DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}