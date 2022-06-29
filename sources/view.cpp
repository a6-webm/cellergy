#include "view.hpp"
#include "cellUniverse.hpp"
#include "raylib.h"
#include <cmath>
#include <iostream>

RenderTexture2D universeTexture;
template <typename T>
struct Box {T left; T right; T top; T bottom;};
Box<int> lastDraw = {0,0,0,0};
Box<float> lastRenderedView = {0, 0, 0, 0};
Vector2 lastViewSize = {0,0};

void reDrawUniverse(frame_data frData, bool resizeVerseTexture) {
    if (resizeVerseTexture) {
        lastViewSize = {frData.view.width,frData.view.height};

        lastRenderedView.left = frData.view.x - (frData.renderRange * frData.view.width + 1);
        lastRenderedView.right = frData.view.x + ((frData.renderRange + 1) * frData.view.width + 1);
        lastRenderedView.top = frData.view.y - (frData.renderRange * frData.view.height + 1);
        lastRenderedView.bottom = frData.view.y + ((frData.renderRange + 1) * frData.view.height + 1);

        lastDraw.left = std::min(VERSE_W-1, static_cast<int>(std::max(0.0f, lastRenderedView.left)));
        lastDraw.right = std::min(VERSE_W-1, static_cast<int>(std::max(0.0f, lastRenderedView.right)));
        lastDraw.top = std::min(VERSE_H-1, static_cast<int>(std::max(0.0f, lastRenderedView.top)));
        lastDraw.bottom = std::min(VERSE_H-1, static_cast<int>(std::max(0.0f, lastRenderedView.bottom)));

        universeTexture = LoadRenderTexture(lastDraw.right-lastDraw.left+1, lastDraw.bottom-lastDraw.top+1);
        std::cout << "resized verseTexture" << std::endl;
    }

    BeginTextureMode(universeTexture);

    ClearBackground(GRAY);

    const int (&verseView)[VERSE_W][VERSE_W] = getCellUniverseRef();
    for (int x = lastDraw.left; x <= lastDraw.right; x++)
        for (int y = lastDraw.top; y <= lastDraw.bottom; y++)
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
            DrawPixel(x - lastDraw.left, y - lastDraw.top, {r, g, b, 255});
        }
    EndTextureMode();
}

void drawUI(frame_data data) {

}

void drawFrame(frame_data frData){
    bool viewOutsideOfLastView = frData.view.x < lastRenderedView.left
                                 || frData.view.y < lastRenderedView.top
                                 || frData.view.x + frData.view.width > lastRenderedView.right
                                 || frData.view.y + frData.view.height > lastRenderedView.bottom;
    bool viewIsSmall = frData.view.width < lastViewSize.x/2
                        || frData.view.height < lastViewSize.y/2;
    if (frData.universeStepped || viewOutsideOfLastView || viewIsSmall) {
        reDrawUniverse(frData, viewOutsideOfLastView || viewIsSmall);
        std::cout << "redrew Universe" << std::endl;
    }
    BeginDrawing();
    ClearBackground(WHITE); //TODO keep in mind, this line only needed so empty texture doesn't flash screen black and white
    DrawTexturePro(
            universeTexture.texture,
            {0,0,(float)universeTexture.texture.width,-(float)universeTexture.texture.height},
            {
                -(frData.view.x - lastDraw.left)*(frData.screen_width/frData.view.width),
                -(frData.view.y - lastDraw.top)*(frData.screen_width/frData.view.width),
                (float)frData.screen_width * universeTexture.texture.width/frData.view.width,
                (float)frData.screen_height * universeTexture.texture.height/frData.view.height
                },
            { 0, 0 },
            0,
            WHITE
    );
    drawUI(frData);

    EndDrawing();
}
