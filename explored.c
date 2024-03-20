#include "explored.h"
#include "node.h"
#include "constants.h"
#include <stdlib.h>

int factorialResults[NUM_TILES-1];

struct Explored newExplored(int size)
{
    struct Explored explored;
    explored.uniqueNodes = calloc(sizeof(struct Node*), size);
    explored.numStored = 0;

    return explored;    
}

int inExplored(struct Explored *explored, struct Node *node, int index)
{
    return explored->uniqueNodes[index] != NULL;
}

void appendBoard(struct Explored *explored, struct Node *node, int index)
{
    explored->uniqueNodes[index] = node;
    explored->numStored++;
}

int factorial(int num)
{
    int retVal = 1;
    while (num > 0)
    {
        retVal *= num--;
    }
}

static inline int tallyLessThan(char state[MAX_D][MAX_D], int startX, int startY, int numTiles) // helper function for findPermPos
{

    int tally = 0;
    //int initX = startPos % MAX_D;
    //int initY = startPos / MAX_D; // was floor
    int i, x, y;
    char checkVal = state[startY][startX];

    for (x = startX + 1, y = startY; y < MAX_D; x++)
    {
        //x = i % MAX_D;
        //y = i / MAX_D; // was floor
        // code block below manually finds the x, y vals, does same thing as block above ^ but roughly 29% faster.
        // This function (tallyLessThan) gets called ~6M times in worst case, and account(ed) for roughly 70%
        // of the total time for BFS. % and / are expensive, so changing to addition in block below
        // reduced the % of BFS that tallyLessThan accounts for to only ~8.7%.
        if (x == MAX_D)
        {
            x = 0;
            y++;
            if (y == MAX_D)
            {
                return tally;
            }
        }

        // separate check for blankChar, since arbitrarily defined, might be lexicographically greater than checkVal,
        // but needs to be treated as though it were '0'
        // more likely to be < checkVal than == to blankChar, since only one blankChar, potentially several < checkVal
        if (state[y][x] < checkVal || state[y][x] == blankChar)
        {
            tally++;
        } 
    }
    return tally;
}

// Effectively finds what position the state would be in if all 9! permutations were sorted in a container.
// Note: ALL 9! permutations, NOT the 9!/2 **possible** permutations (states) from a given starting position.
// 
int findPermPos(char state[MAX_D][MAX_D]) 
{
// with thanks to Gareth Rees here: https://stackoverflow.com/questions/12146910/finding-the-lexicographic-index-of-a-permutation-of-a-given-array
// post clarified an issue I had with a previous recursive implementation
    int index = 0;
    int x, y, position;
 
    for (position = 0, x = 0, y = 0; y < MAX_D; position++, x++)
    {
        if (x == MAX_D)
        {
            x = 0;
            y++;
            if (y == MAX_D)
            {
                return index;
            }
        }
        // essentially index += factorial(NUM_TILES-1-pos) * tallyLessThan(state, pos, NUM_TILES);,
        // factorial results now stored for 0-8 in array (factorialResults) to eliminate duplicate computation
        index += factorialResults[NUM_TILES-1-position] * tallyLessThan(state, x, y, NUM_TILES);

    }
    
    return index;
}

void populateFactorialResults()
{
    short i;
    for (i = 0; i < NUM_TILES; i++)
    {
        factorialResults[i] = factorial(i);
    }
}