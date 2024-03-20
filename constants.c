#include "constants.h"

char gState[MAX_D][MAX_D]={
                            {'1',       '2',       '3'}, // swapped 3 and 6
                            {'4',       '5',       '6'},
                            {'7',       '8', blankChar}
                          };


char sState[MAX_D][MAX_D]={
                            {blankChar, '8',       '3'},
                            {'4',       '6',       '2'},
                            {'7',       '5',       '1'}
                          };

/*
//An alternative start state, a mirror-image of the goal state. 
//   Provides a test for code that requires near-entire enumeration of state space.
char sState[MAX_D][MAX_D]={
                            {blankChar,'8', '7'},
                            {'6'      ,'5', '4'},
                            {'3'      ,'2', '1'}
                           };
*/
