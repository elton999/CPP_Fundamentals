#include "raylib.h"
#include "raymath.h"
#include "Prop.h"

Prop::Prop(Texture2D texture, Vector2 pos) : texture(texture), worldPos(pos) {}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale};
}

void Prop::Render(Vector2 knightPos)
{
    DrawTextureEx(texture, Vector2Subtract(worldPos, knightPos), 0, scale, WHITE);
}