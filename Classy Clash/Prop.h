#include "raylib.h"

class Prop
{
public:
    Prop(Texture2D texture, Vector2 worldPos);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);

private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
};