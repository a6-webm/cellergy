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

void cellUniverseDisplayer_debug()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(30);

    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    const int idk_w = (SCREEN_HEIGHT * VERSE_W) / VERSE_H - 2;
    const int idk_h = SCREEN_HEIGHT - 2;

    while (!WindowShouldClose())
    {
        BeginTextureMode(target);

        ClearBackground(BLACK);
        DrawRectangleLines(0,0,idk_w+2,idk_h+2,WHITE);

        const int (&verseView)[VERSE_W][VERSE_W] = getCellUniverseRef(); // TODO untested
        for (int x = 0; x < VERSE_W; ++x)
            for (int y = 0; y < VERSE_H; ++y)
            {
                if (verseView[x][y] != 0)
                {
                    int max_val = 35;

                    double v = (double)verseView[x][y] / max_val;
                    unsigned char r = round(sin(2 * PI * v + 2)) * 127 + 128;
                    unsigned char g = round(sin(2 * PI * v + 0)) * 127 + 128;
                    unsigned char b = round(sin(2 * PI * v + 4)) * 127 + 128;

                    int x_out = (x*idk_w)/VERSE_W + 1;
                    int y_out = (y*idk_h)/VERSE_H + 1;
                    int width_out = idk_w/VERSE_W;
                    int height_out = idk_h/VERSE_H;

                    DrawRectangle(x_out,y_out,width_out,height_out,{r,g,b,255});
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