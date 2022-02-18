
bool isUniverse1 { true };
const int VERSE_W = 400;
const int VERSE_H = 200;
unsigned short cell_universe_1[VERSE_W][VERSE_H];
unsigned short cell_universe_2[VERSE_W][VERSE_H];

void step()
{
    for (int i_x = 0; i_x < VERSE_W; ++i_x)
    {
        for (int i_y = 0; i_y < VERSE_H; ++i_y)
        {
            sim_cell(i_x,i_y);
        }
    }
}

// Simulates the action of the cell at coordinates (x,y)
void sim_cell(int x, int y)
{

}