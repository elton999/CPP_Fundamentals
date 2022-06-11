#include "raylib.h"

int main(void)
{
    int width{800};
    int height{450};

    Vector2 circle_position{200, 200};
    int circle_radios{25};
    // circle edges
    int l_circle_x{circle_position.x - circle_radios};
    int r_circle_x{circle_position.x + circle_radios};
    int u_circle_y{circle_position.y - circle_radios};
    int b_circle_y{circle_position.y + circle_radios};

    Vector2 axe_position{300, 0};
    Vector2 axe_size{50, 50};
    // axe edges
    int l_axe_x{axe_position.x};
    int r_axe_x{axe_position.x + axe_size.x};
    int u_axe_y{axe_position.y};
    int b_axe_y{axe_position.y + axe_size.y};

    int direction{10};

    bool collision_with_axe{true};

    InitWindow(width, height, "Axe Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe)
            DrawText("Game Over!", 350, 200, 20, RED);
        else
        {
            // Game logic begins

            DrawCircleV(circle_position, circle_radios, BLUE);
            DrawRectangleV(axe_position, axe_size, RED);

            axe_position.y += direction;
            if (axe_position.y > height - axe_size.y || axe_position.y < 0)
                direction = -direction;

            if (IsKeyDown(KEY_D) && circle_position.x < width - circle_radios)
                circle_position.x += 10;

            if (IsKeyDown(KEY_A) && circle_position.x > circle_radios)
                circle_position.x -= 10;

            // Game logic ends
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}