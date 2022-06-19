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
        int moveSpeed;
    } Player;
    Player player = {100,100, 1};
    Vector2 viewTarget;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_W)) player.y -= player.moveSpeed;
        if (IsKeyDown(KEY_S)) player.y += player.moveSpeed;
        if (IsKeyDown(KEY_A)) player.x -= player.moveSpeed;
        if (IsKeyDown(KEY_D)) player.x += player.moveSpeed;

        float zoomRate = 0.03f;
        if (IsKeyDown(KEY_Q)) {
            frData.view.width -= frData.view.width*zoomRate;
            frData.view.height = frData.view.width*SCREEN_HEIGHT/SCREEN_WIDTH;
            if (frData.view.width < 0)
                frData.view.width = frData.view.height = 0.0f;
            else {
                frData.view.x += frData.view.width*zoomRate/2;
                frData.view.y += frData.view.height*zoomRate/2;
            }
        }
        if (IsKeyDown(KEY_E)) {
            frData.view.width += frData.view.width*zoomRate;
            frData.view.height = frData.view.width*SCREEN_HEIGHT/SCREEN_WIDTH;
            frData.view.x -= frData.view.width*zoomRate/2;
            frData.view.y -= frData.view.height*zoomRate/2;
        }

        viewTarget.x = player.x - frData.view.width/2;
        viewTarget.y = player.y - frData.view.height/2;


        float lerpRate = GetFrameTime()*4.0f;
        float lerpThresh = 0.01f;
        if (std::abs(viewTarget.x - frData.view.x) < lerpThresh) {
            frData.view.x = viewTarget.x;
        } else
            frData.view.x += lerpRate*(viewTarget.x - frData.view.x);
        if (std::abs(viewTarget.y - frData.view.y) < lerpThresh) {
            frData.view.y = viewTarget.y;
        } else
            frData.view.y += lerpRate*(viewTarget.y - frData.view.y);

        frData.universeStepped = false;
        if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_N)) {
            step();
            frData.universeStepped = true;
        }

        drawFrame(frData);
    }

    CloseWindow();
}