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
            {0,VERSE_W-1,0,VERSE_H-1},
            false,
            {0,0,VERSE_W,VERSE_H},
            0
            };

    while (!WindowShouldClose())
    {
        frData.reDrawUniverse = false;
        if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_N)) {
            step();
            frData.reDrawUniverse = true;
        }

        drawFrame(frData);
    }

    CloseWindow();
}