typedef struct frame_data {
    unsigned int screen_width, screen_height;
    typedef struct Box {unsigned int left; unsigned int right; unsigned int top; unsigned int bottom;} Box;
    Box draw;
    bool reDrawUniverse;
    Rectangle view;
    unsigned char simState;
} frame_data;

void drawFrame(frame_data frData);