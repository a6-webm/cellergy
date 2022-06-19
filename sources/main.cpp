#ifndef RAYLIB_H
#include "raylib.h"
#endif
#include "cellUniverse.hpp"
#include "view.hpp"
#include <cmath>
#include <iostream>
#include <random>

#define SCREEN_WIDTH (900)
#define SCREEN_HEIGHT (900)

#define WINDOW_TITLE "Window title"

void mvcLoop();

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
//    std::uniform_int_distribution<int> int_dist(0,1);
    std::binomial_distribution<int> binom_dist(1,.2);

    int verseStart[VERSE_W][VERSE_W];
    for (auto & x : verseStart)
        for (int & y : x)
            y = binom_dist(rng) * 6;

    setCellUniverse(verseStart);
    mvcLoop();
    return 0;
}

void mvcLoop() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(30);

    bool init = true;

    frame_data frData = {
            SCREEN_WIDTH, SCREEN_HEIGHT,
            {100,100,32,32},
            2.0f,
            false,
            0
            };

    typedef struct Player {
        int x;
        int y;

    } Player;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_W)) frData.view.y -= .5f;
        if (IsKeyDown(KEY_S)) frData.view.y += .5f;
        if (IsKeyDown(KEY_A)) frData.view.x -= .5f;
        if (IsKeyDown(KEY_D)) frData.view.x += .5f;

        if (IsKeyDown(KEY_Q)) {
            frData.view.width -= 2.0f;
            frData.view.height -= 2.0f;
            if (frData.view.width < 0) frData.view.width = 0.0f;
            if (frData.view.height < 0) frData.view.height = 0.0f;
        }
        if (IsKeyDown(KEY_E)) {
            frData.view.width += 2.0f;
            frData.view.height += 2.0f;
        }

        frData.universeStepped = false;
        if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_N)) {
            step();
            frData.universeStepped = true;
        }

        drawFrame(frData);
    }

    CloseWindow();
}