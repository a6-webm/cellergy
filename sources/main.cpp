#include "raylib.h"
#include "cellUniverse.hpp"
#include <cmath>
#include <iostream>
#include <random>

#define SCREEN_WIDTH (900)
#define SCREEN_HEIGHT (802)

#define WINDOW_TITLE "Window title"

void raylibUIExample_debug();
void cellUniverseDisplayer_debug();

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> int_dist(0,1);

    int verseStart[VERSE_W][VERSE_W];
    for (auto & x : verseStart)
        for (int & y : x)
            y = int_dist(rng);

    setCellUniverse(verseStart);
    cellUniverseDisplayer_debug();
    return 0;
}

void cellUniverseDisplayer_debug() // TODO test
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(30);

    RenderTexture2D target = LoadRenderTexture(VERSE_W*4, VERSE_H*4);

    while (!WindowShouldClose())
    {
        BeginTextureMode(target);

        ClearBackground(BLACK);

        const int (&verseView)[VERSE_W][VERSE_W] = getCellUniverseRef();
        const field_vector (&fieldView)[VERSE_W][VERSE_H] = getFieldUniverse();
        for (int x = 0; x < VERSE_W; x++)
            for (int y = 0; y < VERSE_H; y++)
            {
                int twox = 2*x;
                int twoy = 2*y;

                int repeat_val = 35;
                double v = (double)verseView[x][y] / repeat_val;
                unsigned char r = round(sin(2 * PI * v + 2)) * 127 + 128;
                unsigned char g = round(sin(2 * PI * v + 0)) * 127 + 128;
                unsigned char b = round(sin(2 * PI * v + 4)) * 127 + 128;

                DrawRectangle(twox,twoy,2,2,{r,g,b,255});

                field_vector field = fieldView[x][y];
                repeat_val = 200;
                v = ((double)abs(field.x) + abs(field.y)) / repeat_val;
                r = round(sin(2 * PI * v + 2)) * 127 + 128;
                g = round(sin(2 * PI * v + 0)) * 127 + 128;
                b = round(sin(2 * PI * v + 4)) * 127 + 128;

                if (field.x == 0 && field.y == 0) {
                    DrawPixel(twox,twoy,{0,0,0,255});
                    DrawPixel(twox,twoy,{0,0,0,255});
                } else {
                    int dx = field.x > 0 ? 1 : 0;
                    int dy = field.y > 0 ? 1 : 0;
                    int wid = field.x == 0 ? 2 : 1;
                    int hei = field.y == 0 ? 2 : 1;
                    DrawRectangle(twox+dx,twoy+dy,wid,hei,{r,g,b,255});
                }
            }
        EndTextureMode();

        BeginDrawing();

        DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);

        EndDrawing();

        WaitTime(100);

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