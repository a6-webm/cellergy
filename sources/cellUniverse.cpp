#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include "cellUniverse.hpp"

typedef struct field_vector
{
    int x;
    int y;
} field_vector;


bool isInit {false};
bool isUniverse1 { false };

int sub_cell_values_1[VERSE_W][VERSE_H];
int sub_cell_values_2[VERSE_W][VERSE_H];
field_vector sub_cell_fields_1[VERSE_W][VERSE_H];
field_vector sub_cell_fields_2[VERSE_W][VERSE_H];

const int CELL_MAX = INT_MAX / 2;

int (&currVerse())[VERSE_W][VERSE_H]
{
    if (isUniverse1)
        return sub_cell_values_1;
    return sub_cell_values_2;
}

int (&prevVerse())[VERSE_W][VERSE_H]
{
    if (isUniverse1)
        return sub_cell_values_2;
    return sub_cell_values_1;
}

field_vector (&currVerseFields())[VERSE_W][VERSE_H]
{
    if (isUniverse1)
        return sub_cell_fields_1;
    return sub_cell_fields_2;
}

field_vector (&prevVerseFields())[VERSE_W][VERSE_H]
{
    if (isUniverse1)
        return sub_cell_fields_2;
    return sub_cell_fields_1;
}

// Updates the fields of the verse assuming a cell of strength "strength" is at ("x","y")
void updateFields(int x, int y, int strength) // TODO untested
{
    for (int d_y = -strength + 1; d_y <= strength - 1; ++d_y)
        for(int d_x = -(strength - abs(d_y) - 1); d_x <= strength - abs(d_y) - 1; ++d_x)
        {
            if (d_x < 0)
                currVerseFields()[x + d_x][y + d_y].x += -strength - d_x;
            else if (d_x != 0)
                currVerseFields()[x + d_x][y + d_y].x += strength - d_x;

            if (d_y < 0)
                currVerseFields()[x + d_x][y + d_y].y += -strength - d_y;
            else if (d_y != 0)
                currVerseFields()[x + d_x][y + d_y].y += strength - d_y;
        }
}

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y) // TODO What even are we trying to do with the sim_cell() function lmao
{

}

void step()
{
    // Swap current universe
    isUniverse1 = !isUniverse1;

    // Clear new universe
    memset((void *) currVerse(), 0, sizeof(currVerse())); // TODONE test if this actually clears this
    memset((void *) currVerseFields(), 0, sizeof(currVerse()));

    // Simulate
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
            sim_cell(i_x,i_y);
}

const int (&getCellUniverseRef())[VERSE_W][VERSE_H]
{
    return currVerse();
}

void setCellUniverse(int (&x)[VERSE_W][VERSE_H])
{
    for (int i = 0; i < VERSE_W; ++i)
        for (int j = 0; j < VERSE_H; ++j)
            currVerse()[i][j] = x[i][j];
}