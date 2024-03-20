#ifndef EXPLORED
#define EXPLORED
#include "node.h"
#include "constants.h"

struct Explored{
    struct Node **uniqueNodes;
    int numStored;
};

struct Explored newExplored(int size);
int inExplored(struct Explored *explored, struct Node *node, int index);
void appendBoard(struct Explored *explored, struct Node *node, int index);
int factorial(int num);
static inline int tallyLessThan(char state[MAX_D][MAX_D], int startX, int startY, int numTiles);
int findPermPos(char state[MAX_D][MAX_D]);
void populateFactorialResults();

#endif