// These can be modified
// -----------------------
const int VERSE_W = 5;
const int VERSE_H = 5;
// -----------------------



// // Initialises variables
// void universeInit();

// Performs one time step of the universe
void step();

// Set the current universe
void setCellUniverse(const int (*const provided)[VERSE_W][VERSE_H]);

// Get a pointer to a pointer to the current cell universe
const int (*const *getCellUniverse())[VERSE_W][VERSE_H];