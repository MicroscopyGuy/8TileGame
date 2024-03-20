
#ifndef NODE
#define NODE

#include "constants.h"

struct Node
{
    char board[MAX_D][MAX_D];
    struct Node *next; //used for the fringe (queue), linked list based
    struct Node *prev; //refers to a node's singular parent
    short bX;
    short bY;    
};

void printState(struct Node *node);
void swapTile(struct Node *node, enum swapDir direction);
void makeSameState(struct Node *node1, struct Node *node2);
struct Node *makeInitialState();
#endif