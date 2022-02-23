#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <climits>
#include <iostream>
#include "cellUniverse.h"

typedef struct field_vector
{
    int x;
    int y;
} field_vector;


bool isInit {false};
bool isUniverse1 { false };

// const int VERSE_W;
// const int VERSE_H;

int sub_cell_values_1[VERSE_W][VERSE_H];
int sub_cell_values_2[VERSE_W][VERSE_H];
field_vector sub_cell_fields_1[VERSE_W][VERSE_H];
field_vector sub_cell_fields_2[VERSE_W][VERSE_H];

int (*cell_universe)[VERSE_W][VERSE_H];
field_vector (*field_universe)[VERSE_W][VERSE_H];
int (*prev_cell_universe)[VERSE_W][VERSE_H];
field_vector (*prev_field_universe)[VERSE_W][VERSE_H];

const int CELL_MAX = INT_MAX/2;

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y) // [ ] What even are we trying to do with the sim_cell() function lmao
{
    
}

void step()
{
    // Swap current universe
    isUniverse1 = !isUniverse1;
    if (isUniverse1)
    {
        cell_universe = &sub_cell_values_1;
        prev_cell_universe = &sub_cell_values_2;
        field_universe = &sub_cell_fields_1;
        prev_field_universe = &sub_cell_fields_2;
    } else
    {
        cell_universe = &sub_cell_values_2;
        prev_cell_universe = &sub_cell_values_1;
        field_universe = &sub_cell_fields_2;
        prev_field_universe = &sub_cell_fields_1;
    }
    
    // Clear new universe
    memset(*cell_universe, 0, sizeof(*cell_universe)); // [x] test if this actually clears this
    memset(*field_universe, 0, sizeof(*field_universe));
    
    // Simulate
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
            sim_cell(i_x,i_y);
}

const int (*const *getCellUniverse())[VERSE_W][VERSE_H] // [ ] test if this is the correct return type
{
    return (const int (* const*)[VERSE_W][VERSE_H])&cell_universe;
}


#ifdef _DEBUG_cellUniverse
void versePrint(int (*verse)[VERSE_W][VERSE_H])
{
    for (int i = 0; i < VERSE_W; i++)
    {
        for (int j = 0; j < VERSE_H; j++)
        {
            std::cout << (*verse)[i][j] << "|";
        }
        std::cout << std::endl;
    }
    
}

void versePrint(field_vector (*verse)[VERSE_W][VERSE_H])
{
    for (int i = 0; i < VERSE_W; i++)
    {
        std::cout << "|";
        for (int j = 0; j < VERSE_H; j++)
        {
            std::cout << (*verse)[i][j].x << "," << (*verse)[i][j].y << "|";
        }
        std::cout << std::endl;
    }
}

void runFor(int numCycles)
{
    for (int i = 0; i < numCycles; i++)
    {
        versePrint(cell_universe);
        step();
        // [ ] add a sleep function here
    }
    std::cout << "Done. Ran for " << i << "cycles" << std::endl;
}

int main(int argc, char const *argv[])
{
    int mySubVerse[VERSE_W][VERSE_H];

    for (int i = 0; i < VERSE_W; i++)
    {
        for (int j = 0; j < VERSE_H; j++)
        {
            mySubVerse[i][j] = i * j;
        }
    }

    int (*myVerse)[VERSE_W][VERSE_H];
    int (*myVerse2)[VERSE_W][VERSE_H];
    myVerse = &mySubVerse;
    myVerse2 = &mySubVerse;


    versePrint(myVerse);

    memset(*myVerse, 0, sizeof(*myVerse));
    versePrint(myVerse2);

    return 0;
}
#endif