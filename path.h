#ifndef PATH
#define PATH

#include "node.h"
#include "constants.h"

struct Path
{
    int size;
    char boardStates[MAX_PATH][MAX_D][MAX_D];
};

struct Path newPath();
void appendBoardToPath(struct Path *path, struct Node *node); //must change size
void makePath(struct Path *path, struct Node *finalNode);
void printPath(struct Path *path);

#endif