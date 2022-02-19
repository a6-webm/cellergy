// Initialises variables
void universeInit();

// Performs one time step of the universe
void step();

// Set the current universe
void setCellUniverse(const int** provided);

// Get a pointer to a pointer to the current cell universe
const int**** getCellUniverse();