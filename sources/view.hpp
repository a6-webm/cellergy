#pragma once
#ifndef RAYLIB_H
#include "raylib.h"
#endif

typedef struct frame_data {
    int screen_width, screen_height;
    Rectangle view;
    float renderRange;
    bool universeStepped;
    unsigned char simState;
} frame_data;

void drawFrame(frame_data frData);