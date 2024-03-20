#include "path.h"
#include "node.h"
#include <stdio.h>

/***************************************************************************************
 Contains a 3-d array consisting of 1-100 board states
 **************************************************************************************/
struct Path newPath()
{
    struct Path path;
    path.size = 0;
    return path;
}

void appendBoardToPath(struct Path *path, struct Node *node) //must change size
{
    int j, k;
    for (j = 0; j < MAX_D; j++)
    {
        for (k = 0; k < MAX_D; k++)
        {
            path->boardStates[path->size][j][k] = node->board[j][k];
            path->size++;
        }
    }
}

void makePath(struct Path *path, struct Node *finalNode)
{
    int i, j, k;
    struct Node *iterator;
    iterator = finalNode;
    for(i = MAX_PATH-1; i >= 0 && iterator != NULL; i--, iterator = iterator->prev, path->size++)
    {
        for (j = 0; j < MAX_D; j++)
        {
            for (k = 0; k < MAX_D; k++)
            {
                path->boardStates[i][j][k] = iterator->board[j][k];   
            }
        }   
    }    
}

void printPath(struct Path *path)
{
    int i,j,k;
    for (i = MAX_PATH - (path->size), k = 0; i < MAX_PATH; i++, k++)
    {
        printf("***State #:%d***\n", k);
        for (j = 0; j < MAX_D; j++)
        {
            printf("%c   %c   %c\n", path->boardStates[i][j][0], path->boardStates[i][j][1], path->boardStates[i][j][2]);
        }
        printf("******************\n\n");
    }
}
