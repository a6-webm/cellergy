#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include <random>
#include "cellUniverse.hpp"

bool isUniverse1 { false };

std::random_device dev;
std::mt19937 gen(dev());

int sub_cell_values_1[VERSE_W][VERSE_H];
int sub_cell_values_2[VERSE_W][VERSE_H];

const int CELL_MAX = INT_MAX / 2;

Player prevPlayer;
Player currPlayer;

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

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y) {
    int aliveCount = 0;
    for (int d_y = -1; d_y <= 1; ++d_y)
        for (int d_x = -1; d_x <= 1; ++d_x) {
            int dd_x = d_x;
            int dd_y = d_y;
            if (x+d_x < 0) dd_x = VERSE_W-1 - x;
            if (x+d_x >= VERSE_W) dd_x = -x;
            if (y+d_y < 0) dd_y = VERSE_H-1 - y;
            if (y+d_y >= VERSE_H) dd_y = -y;
            if (prevVerse()[x+dd_x][y+dd_y] == 2) ++aliveCount;
        }

    if (prevVerse()[x][y] == 0) {
        if (aliveCount == 3) {
            currVerse()[x][y] += 2;
            currPlayer.energy -= 2;
        }
    } else if (aliveCount == 2 || aliveCount == 3) {
        currVerse()[x][y] += 2;
    } else {
        currPlayer.energy += 2;
    }
}

void sim_player() {
    if (currPlayer.sim) {
        // TODO implement the player being able to act like a simulated cell
    } else {
        currPlayer.energy += prevPlayer.val - currPlayer.val + currVerse()[currPlayer.x][currPlayer.y];
        currVerse()[currPlayer.x][currPlayer.y] = currPlayer.val;
    }
}

Player step(Player newPlayer) {
    // Swap current universe
    isUniverse1 = !isUniverse1;
    prevPlayer = currPlayer;
    currPlayer = newPlayer;

    // Clear new universe
    memset((void *) currVerse(), 0, sizeof(currVerse()));

    // Simulate new cells
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
            if (i_x != prevPlayer.x || i_y != prevPlayer.y)
                sim_cell(i_x,i_y);

    sim_player();

    return currPlayer;
}

void setCellUniverse(int (&x)[VERSE_W][VERSE_H]) {
    int (&verse)[VERSE_W][VERSE_H] = currVerse();
    for (int i = 0; i < VERSE_W; ++i)
        for (int j = 0; j < VERSE_H; ++j)
            verse[i][j] = x[i][j];
}

const int (&getCellUniverseRef())[VERSE_W][VERSE_H] {
    return currVerse();
}