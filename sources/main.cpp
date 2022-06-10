#include "raylib.h"
#include "cellUniverse.hpp"
#include <cmath>
#include <iostream>
#include <random>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (800)

#define WINDOW_TITLE "Window title"

void raylibUIExample_debug();
void cellUniverseDisplayer_debug();

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
//    std::uniform_int_distribution<int> int_dist(0,1);
    std::binomial_distribution<int> binom_dist(1,.5);

    int verseStart[VERSE_W][VERSE_W];
    for (auto & x : verseStart)
        for (int & y : x)
            y = binom_dist(rng);

    setCellUniverse(verseStart);
    cellUniverseDisplayer_debug();
    return 0;
}

void cellUniverseDisplayer_debug() // TODO make cells and fields more distinguishable
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(30);

    RenderTexture2D target = LoadRenderTexture(VERSE_W*3, VERSE_H*3);

    bool init = true;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_N)) {
            step();

            BeginTextureMode(target);

            ClearBackground(GRAY);

            const int (&verseView)[VERSE_W][VERSE_W] = getCellUniverseRef();
            const field_vector (&fieldView)[VERSE_W][VERSE_H] = getFieldUniverse();
            for (int x = 0; x < VERSE_W; x++)
                for (int y = 0; y < VERSE_H; y++)
                {
                    int gridx = 3 * x;
                    int gridy = 3 * y;

                    double v;
                    unsigned char r;
                    unsigned char g;
                    unsigned char b;

                    int repeat_val = 20;
                    if (verseView[x][y] == 0) {
                        r = g = b = 0;
                    } else {
                        v = (double)verseView[x][y] / repeat_val;
                        r = round(sin(2 * PI * v + 2)) * 127 + 128;
                        g = round(sin(2 * PI * v + 0)) * 127 + 128;
                        b = round(sin(2 * PI * v + 4)) * 127 + 128;
                    }
                    DrawRectangle(gridx, gridy, 2, 2, {r, g, b, 255});

                    field_vector field = fieldView[x][y];
                    repeat_val = 5;
                    if (field.x == 0 && field.y == 0) {
                        DrawPixel(gridx, gridy, {0, 0, 0, 255});
                        DrawPixel(gridx+1, gridy+1, {0, 0, 0, 255});
                    } else {
                        v = ((double)abs(field.x) + abs(field.y)) / repeat_val;
                        r = g = b = (v * 255 < 255 ? v * 255 : 255);
                        int dx = field.x > 0 ? 1 : 0;
                        int dy = field.y > 0 ? 1 : 0;
                        int wid = field.x == 0 ? 2 : 1;
                        int hei = field.y == 0 ? 2 : 1;
                        DrawRectangle(gridx + dx, gridy + dy, wid, hei, {r, g, b, 255});
                    }
                }
            EndTextureMode();
        }

        BeginDrawing();

        ClearBackground(WHITE);
        DrawTextureNPatch(
                target.texture,
                {
                        {0,0,(float)target.texture.width,(float)-target.texture.height},
                        0,0,0,0,0
                        },
                { 0, 0, 800, 800 },
                { 0, 0 },
                0,
                WHITE
        );

        EndDrawing();
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