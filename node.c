#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "constants.h"

void printState(struct Node *node) 
{
    int i;
    for (i=0; i < MAX_D; i++)
    {
        printf("[%d][0]: %c, [%d][1]: %c, [%d][2]: %c\n", i, node->board[i][0], i, node->board[i][1], i, node->board[i][2]);
    }
}

void swapTile(struct Node *node, enum swapDir direction)
{
    //direction specifically refers to the direction of movement of the blank tile
    char temp;
    short bX = node->bX;
    short bY = node->bY;
    switch(direction)
    {
        case up:    temp = node->board[bY-1][bX];
                    node->board[bY-1][bX] = node->board[bY][bX];
                    node->board[bY][bX] = temp;
                    node->bY--;
                    break;

        case down:  temp = node->board[bY+1][bX];
                    node->board[bY+1][bX] = node->board[bY][bX];
                    node->board[bY][bX] = temp;
                    node->bY++;
                    break;  

        case left:  temp = node->board[bY][bX-1];
                    node->board[bY][bX-1] = node->board[bY][bX];
                    node->board[bY][bX] = temp;
                    node->bX--;
                    break;

        case right: temp = node->board[bY][bX+1];
                    node->board[bY][bX+1] = node->board[bY][bX];
                    node->board[bY][bX] = temp;
                    node->bX++;
                    break;
    }
}

void makeSameState(struct Node *node1, struct Node *node2) // could make use of memcpy
{
    /* node2 is made to be the same as node1 except:
       1) node2->prev is node1, since node1 is the parent
       2) node2->next is still NULL, that is only used for the linked list that makes up the explored nodes array
    */
    int i, j;  
    for (i = 0; i < MAX_D; i++) 
    {
        for (j = 0; j < MAX_D; j++) 
        {
            node2->board[i][j] = node1->board[i][j];
        }
    }
    node2->bY = node1->bY;
    node2->bX = node1->bX; 
}

struct Node* makeInitialState()
{
    struct Node *node = malloc(sizeof(struct Node));
    int i, j;
    for (i = 0; i < MAX_D; i++)
    {
        for (j = 0; j < MAX_D; j++)
        {
            node->board[i][j] = sState[i][j];
            if (sState[i][j] == blankChar) 
            {
                node->bY = i;
                node->bX = j;
            }
        }
    }
    node->next = NULL;
    node->prev = NULL;
    return node;
}
