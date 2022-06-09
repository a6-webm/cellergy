#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include "cellUniverse.hpp"

typedef struct field_vector {
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

int (&currVerse())[VERSE_W][VERSE_H] {
    if (isUniverse1)
        return sub_cell_values_1;
    return sub_cell_values_2;
}

int (&prevVerse())[VERSE_W][VERSE_H] {
    if (isUniverse1)
        return sub_cell_values_2;
    return sub_cell_values_1;
}

field_vector (&currVerseFields())[VERSE_W][VERSE_H] {
    if (isUniverse1)
        return sub_cell_fields_1;
    return sub_cell_fields_2;
}

field_vector (&prevVerseFields())[VERSE_W][VERSE_H] {
    if (isUniverse1)
        return sub_cell_fields_2;
    return sub_cell_fields_1;
}

// Updates the fields of the verse assuming a cell of strength "strength" is at ("x","y")
void updateFields(int x, int y, int strength) { // TODO untested
    field_vector (&verseF)[VERSE_W][VERSE_H] = currVerseFields();
    for (int d_y = -strength + 1; d_y <= strength - 1; ++d_y) {
        int end = strength - abs(d_y) - 1;
        for(int d_x = -(strength - abs(d_y) - 1); d_x <= end; ++d_x) {
            if (d_x < 0)
                verseF[x + d_x][y + d_y].x += -strength - d_x;
            else if (d_x != 0)
                verseF[x + d_x][y + d_y].x += strength - d_x;

            if (d_y < 0)
                verseF[x + d_x][y + d_y].y += -strength - d_y;
            else if (d_y != 0)
                verseF[x + d_x][y + d_y].y += strength - d_y;
        }
    }
}

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y) { // TODO Implement this from TODO.txt


}

void calculate_field(int x, int y) { // TODO Implement this (because fields need to be calculated before cells move)

}

void step() {
    // Swap current universe
    isUniverse1 = !isUniverse1;

    // Clear new universe
    memset((void *) currVerse(), 0, sizeof(currVerse()));
    memset((void *) currVerseFields(), 0, sizeof(currVerse())); // TODO test that this doesn't mess up cause structs

    // Simulate
    for (int i_x = 1; i_x < VERSE_W - 1; ++i_x)
        for (int i_y = 1; i_y < VERSE_H - 1; ++i_y)
            sim_cell(i_x,i_y);

    // Populate fields
    for (int i_x = 1; i_x < VERSE_W - 1; ++i_x)
        for (int i_y = 1; i_y < VERSE_H - 1; ++i_y)
            calculate_field(i_x,i_y);
}

const int (&getCellUniverseRef())[VERSE_W][VERSE_H] {
    return currVerse();
}

void setCellUniverse(int (&x)[VERSE_W][VERSE_H]) {
    int (&verse)[VERSE_W][VERSE_H] = currVerse();
    for (int i = 0; i < VERSE_W; ++i)
        for (int j = 0; j < VERSE_H; ++j)
            verse[i][j] = x[i][j];
}