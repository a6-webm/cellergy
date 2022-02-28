// These can be modified
// -----------------------
const int VERSE_W = 400;
const int VERSE_H = 400;
// -----------------------

// Performs one time step of the universe
void step();

// Set the current universe, provided array must not disappear
void setCellUniverse(int (&x)[VERSE_W][VERSE_H]);

// Get a pointer to a pointer to the current cell universe
const int (&getCellUniverseRef())[VERSE_W][VERSE_H];