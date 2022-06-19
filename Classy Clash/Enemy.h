#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    void setTarget(Character *knight) { target = knight; }

private:
    Character *target{};
    float damagePerSecond{10.f};
};

#endif