// Performs one time step of the universe
void step();

// Set the current universe
void setCellUniverse(const unsigned short** provided);

// Get reference to the array currently acting as the current cell universe
unsigned short** getCellUniverse();

// Get reference to the array currently acting as the previous cell universe
unsigned short** getPrevCellUniverse();