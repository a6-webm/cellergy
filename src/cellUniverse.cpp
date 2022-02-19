#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <climits>
#include <iostream>

typedef struct field_vector
{
    int x;
    int y;
} field_vector;


bool isInit {false};
bool isUniverse1 { false };
const int VERSE_W = 5;
const int VERSE_H = 5;
int** sub_cell_values_1;
int** sub_cell_values_2;
field_vector** sub_cell_fields_1;
field_vector** sub_cell_fields_2;
int**** cell_universe;
field_vector**** field_universe;
int**** prev_cell_universe;
field_vector**** prev_field_universe;

const int CELL_MAX = INT_MAX/2;

void universeInit()
{
    sub_cell_values_1 = new int*[VERSE_W];
        for (int i = 0; i < VERSE_W; i++)
            sub_cell_values_1[i] = new int[VERSE_H];
    sub_cell_values_2 = new int*[VERSE_W];
        for (int i = 0; i < VERSE_W; i++)
            sub_cell_values_2[i] = new int[VERSE_H];
    sub_cell_fields_1 = new field_vector*[VERSE_W];
        for (int i = 0; i < VERSE_W; i++)
            sub_cell_fields_1[i] = new field_vector[VERSE_H];
    sub_cell_fields_2 = new field_vector*[VERSE_W];
        for (int i = 0; i < VERSE_W; i++)
            sub_cell_fields_2[i] = new field_vector[VERSE_H];
    
    isInit = true;
}

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y)
{
    
}

void step()
{
    if (!isInit) universeInit();

    // Swap current universe
    isUniverse1 = !isUniverse1;
    if (isUniverse1)
    {
        *cell_universe = &sub_cell_values_1;
        *prev_cell_universe = &sub_cell_values_2;
        *field_universe = &sub_cell_fields_1;
        *prev_field_universe = &sub_cell_fields_2;
    } else
    {
        *cell_universe = &sub_cell_values_2;
        *prev_cell_universe = &sub_cell_values_1;
        *field_universe = &sub_cell_fields_2;
        *prev_field_universe = &sub_cell_fields_1;
    }
    
    // Clear new universe
    memset(**cell_universe, 0, sizeof(cell_universe)); // TODO test if this actually clears this
    memset(**field_universe, 0, sizeof(field_universe));
    
    // Simulate
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
            sim_cell(i_x,i_y);
}

const int** const** getCellUniverse()
{
    return (const int** const**)cell_universe;
}


#ifdef _DEBUG
void versePrint(int*** verse)
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

void versePrint(field_vector*** verse)
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

int main(int argc, char const *argv[])
{
    int** mySubVerse = new int*[VERSE_W];
        for (int i = 0; i < VERSE_W; i++)
            mySubVerse[i] = new int[VERSE_H];

    for (int i = 0; i < VERSE_W; i++)
    {
        for (int j = 0; j < VERSE_H; j++)
        {
            mySubVerse[i][j] = i * j;
        }
    }
    
    int*** myVerse;
    myVerse = &mySubVerse;

    versePrint(myVerse);
    return 0;
}
#endif