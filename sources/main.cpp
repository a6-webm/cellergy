#include "raylib.h"
#include "cellUniverse.hpp"
#include <iostream>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

void raylibUIExample_debug();
void cellUniverseDisplayer_debug();

int main()
{
    cellUniverseDisplayer_debug();
    return 0;
}

void cellUniverseDisplayer_debug()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // TODO write loop for drawing verse

        EndDrawing();

        WaitTime(1000);

        step();
    }

    CloseWindow();
}

void raylibUIExample()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        DrawTexture(texture, texture_x, texture_y, WHITE);

        const char* text = "OMG! IT WORKS!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
}