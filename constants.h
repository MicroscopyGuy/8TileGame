#ifndef CONSTANTS_FOR_TILE_GAME
#define CONSTANTS_FOR_TILE_GAME

#define MAX_D 3
#define NUM_TILES 9
#define MAX_PATH 100
#define PERMUTATIONS 362880
#define TIMING_MODE 0
#define TIMING_MODE_RUNS 10000
#define blankChar '.'


extern int factorialResults[]; // will store factorials for use in the tallyLessThan helper function for findPermPos
enum swapDir{up, down, left, right};// direction is direction of movement of the blank tile during the swap-eration


//const char blankChar = '.';


extern char gState[MAX_D][MAX_D];
extern char sState[MAX_D][MAX_D];


#endif