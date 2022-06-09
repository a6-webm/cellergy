// These can be modified
// -----------------------
const int VERSE_W = 200;
const int VERSE_H = 200;
// -----------------------

typedef struct field_vector {
    int x;
    int y;
} field_vector;

// Performs one time step of the universe
void step();

// Set the current universe, provided array must not disappear
void setCellUniverse(int (&x)[VERSE_W][VERSE_H]);

// Get a reference to the current cell universe
const int (&getCellUniverseRef())[VERSE_W][VERSE_H];

// Get a reference to the current field universe
const field_vector (&getFieldUniverse())[VERSE_W][VERSE_H];