#include "view.hpp"
#include "cellUniverse.hpp"
#include "raylib.h"
#include <cmath>

RenderTexture2D universeTexture;

void drawUI(frame_data data);

void reDrawUniverse(frame_data frData) {
    universeTexture = LoadRenderTexture(frData.draw.right-frData.draw.left, frData.draw.bottom-frData.draw.top);

    BeginTextureMode(universeTexture);

    ClearBackground(GRAY);

    const int (&verseView)[VERSE_W][VERSE_W] = getCellUniverseRef();
    for (int x = frData.draw.left; x <= frData.draw.right; x++)
        for (int y = frData.draw.top; y <= frData.draw.bottom; y++)
        {
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
            DrawPixel(x, y, {r, g, b, 255});
        }
    EndTextureMode();
}

void drawUI(frame_data data) {

}

void drawFrame(frame_data frData){
    if (frData.reDrawUniverse) reDrawUniverse(frData);

    BeginDrawing();
    ClearBackground(WHITE); //TODO keep in mind, this line only needed so empty texture doesn't flash screen black and white
    DrawTextureNPatch(
            universeTexture.texture,
            {
                    {0,0,(float)universeTexture.texture.width,(float)-universeTexture.texture.height},
                    0,0,0,0,0
            },
            { 0, 0, (float)frData.screen_width, (float)frData.screen_height },
            { 0, 0 },
            0,
            WHITE
    );
    drawUI(frData);
    EndDrawing();
}
