#pragma once
// These can be modified
// -----------------------
const int VERSE_W = 400;
const int VERSE_H = 400;
// -----------------------

typedef struct Player {
    int x;
    int y;
    int val;
    bool sim;
    int energy;
} Player;

// Performs one time step of the universe
Player step(Player player);

// Set the current universe, provided array must not disappear
void setCellUniverse(int (&x)[VERSE_W][VERSE_H]);

// Get a reference to the current cell universe
const int (&getCellUniverseRef())[VERSE_W][VERSE_H];