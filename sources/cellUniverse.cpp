#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include <random>
#include "cellUniverse.hpp"

bool isNewUniverse { false };
bool isUniverse1 { false };

std::random_device dev;
std::mt19937 gen(dev());

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

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y) {
    const int (&prevV)[VERSE_W][VERSE_W] = prevVerse();
    const field_vector (&prevF)[VERSE_W][VERSE_H] = prevVerseFields();
    int (&currV)[VERSE_W][VERSE_W] = currVerse();

    field_vector field = prevF[x][y];
    int strength = prevV[x][y];

    if (strength <= 0) return;
    if (strength < 15) {
        int dx, dy = 0;
        if (field.x == 0 && field.y == 0) {
            std::uniform_int_distribution<int> dis(-1, 1);
            dx = dis(gen);
            dy = dis(gen);
        } else {
            if (field.x > 0) dx = -1;
            else if (field.x == 0) dx = 0;
            else dx = 1;
            if (field.y > 0) dy = -1;
            else if (field.y == 0) dy = 0;
            else dy = 1;
        }
        if (x + dx < 0 || x + dx >= VERSE_W) dx = 0;
        if (y + dy < 0 || y + dy >= VERSE_H) dy = 0;
        currV[x+dx][y+dy] += strength;
        return;
    }
    else {
        int dx, dy = 0;
        if (field.x == 0 && field.y == 0) {
            std::uniform_int_distribution<int> dis(-1, 1);
            dx = dis(gen);
            dy = dis(gen);
        } else {
            if (field.x > 0) dx = 1;
            else if (field.x == 0) dx = 0;
            else dx = -1;
            if (field.y > 0) dy = 1;
            else if (field.y == 0) dy = 0;
            else dy = -1;
        }
        if (x + dx < 0 || x + dx >= VERSE_W) dx = 0;
        if (y + dy < 0 || y + dy >= VERSE_H) dy = 0;
        currV[x][y] += strength/2;
        currV[x+dx][y+dy] += strength - strength/2;
        return;
    }
}

void calculate_field(int x, int y) {
    field_vector (&verseF)[VERSE_W][VERSE_H] = currVerseFields();
    int strength = currVerse()[x][y];

    int end_d_y = strength - 1;
    int d_y = -end_d_y;
    if (y+d_y < 0) d_y = -y;
    if (y+end_d_y >= VERSE_H) end_d_y = (VERSE_H - 1) - y;
    while(d_y <= end_d_y) {
        int end_d_x = strength - abs(d_y) - 1;
        int d_x = -end_d_x;
        if (x+d_x < 0) d_x = -x;
        if (x+end_d_x >= VERSE_W) end_d_x = (VERSE_W - 1) - x;
        while (d_x <= end_d_x) {
            if (d_x < 0)
                verseF[x + d_x][y + d_y].x += -strength - d_x;
            else if (d_x > 0)
                verseF[x + d_x][y + d_y].x += strength - d_x;

            if (d_y < 0)
                verseF[x + d_x][y + d_y].y += -strength - d_y;
            else if (d_y > 0)
                verseF[x + d_x][y + d_y].y += strength - d_y;

            ++d_x;
        }
        ++d_y;
    }
}

void step() {
    // Swap current universe
    isUniverse1 = !isUniverse1;

    // Clear new universe
    memset((void *) currVerse(), 0, sizeof(currVerse()));
    memset((void *) currVerseFields(), 0, sizeof(currVerseFields()));

    if (isNewUniverse) { // Only generate fields
        isUniverse1 = !isUniverse1;
        for (int i_x = 0; i_x < VERSE_W; ++i_x)
            for (int i_y = 0; i_y < VERSE_H; ++i_y)
                calculate_field(i_x,i_y);
        isNewUniverse = false;
        return;
    }

    // Simulate new cells
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
            sim_cell(i_x,i_y);

    // Populate new fields
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
            calculate_field(i_x,i_y);
}

void setCellUniverse(int (&x)[VERSE_W][VERSE_H]) {
    int (&verse)[VERSE_W][VERSE_H] = currVerse();
    for (int i = 0; i < VERSE_W; ++i)
        for (int j = 0; j < VERSE_H; ++j)
            verse[i][j] = x[i][j];
    isNewUniverse = true;
}

const int (&getCellUniverseRef())[VERSE_W][VERSE_H] {
    return currVerse();
}

const field_vector (&getFieldUniverse())[VERSE_W][VERSE_H] {
    return currVerseFields();
}