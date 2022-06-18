#include "raylib.h"

class Prop
{
public:
    Prop(Texture2D texture, Vector2 worldPos);

private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
};