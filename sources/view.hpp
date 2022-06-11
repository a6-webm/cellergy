typedef struct frame_data {
    Rectangle draw;
    Rectangle view;
    unsigned char sim_state;
} frame_data;

void drawFrame(frame_data frData);