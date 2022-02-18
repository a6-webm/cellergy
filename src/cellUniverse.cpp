#include <stdio.h>
#include <string.h>

bool isUniverse1 { false };
const int VERSE_W = 400;
const int VERSE_H = 200;
int cell_universe_1[VERSE_W][VERSE_H];
int cell_universe_2[VERSE_W][VERSE_H];
int cell_fields_1[VERSE_W][VERSE_H];
int cell_fields_2[VERSE_W][VERSE_H];

void step()
{
    isUniverse1 = !isUniverse1;
    if (isUniverse1)
    {
        memset(cell_universe_1, 0, sizeof(cell_universe_1));
        memset(cell_fields_1, 0, sizeof(cell_fields_1));
    } else
    {
        memset(cell_universe_2, 0, sizeof(cell_universe_2));
        memset(cell_fields_2, 0, sizeof(cell_fields_2));
    }
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
    {
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
        {
            sim_cell(i_x,i_y);
        }
    }
}

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y)
{

}