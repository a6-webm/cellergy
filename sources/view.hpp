typedef struct frame_data {
    Rectangle draw;
    bool reDrawUniverse;
    Rectangle view;
    unsigned char simState;
} frame_data;

void drawFrame(frame_data frData);