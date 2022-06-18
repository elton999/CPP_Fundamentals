#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    void Tick(float deltaTime);
    void undoMovement();

private:
    float width{}, height{};
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPos{};
    Vector2 worldPos{};
    // 1 : facing right, -1 : facing left
    int rightLeft{1};
    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float scale{4.0};

    Vector2 worldPosLastFrame{};
};