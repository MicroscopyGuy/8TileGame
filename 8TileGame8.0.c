#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <math.h>

#define MAX_D 3
#define NUM_TILES 9
#define MAX_PATH 100
#define PERMUTATIONS 362880

*/
/************************************************************************************************
 Node,Node operations sections of code. Node stores board state along with pertinent information.
*************************************************************************************************/
//5.5 recent changes, added findPermPos,
// made gState and sState const
// added sorted

const char blankChar = '.';

enum swapDir{up, down, left, right};// direction is direction of movement of the blank tile during the swap-eration
char gState[MAX_D][MAX_D]={
                            {'1',       '2',       '3'}, // swapped 3 and 6
                            {'4',       '5',       '6'},
                            {'7',       '8', blankChar}
                          };
/*
char sState[MAX_D][MAX_D]={
                            {blankChar, '8',       '3'},
                            {'4',       '6',       '2'},
                            {'7',       '5',       '1'}
                          };
*/

char sState[MAX_D][MAX_D]={
                            {blankChar,'8', '7'},
                            {'6'      ,'5', '4'},
                            {'3'      ,'2', '1'}
                           };
/*
**************************************
      Column0    Column1    Column2
Row0  x[0][0]    x[0][1]    x[0][2]
Row1  x[1][0]    x[1][1]    x[1][2]
Row2  x[2][0]    x[2][1]    x[2][2]
**************************************  
*/
struct Node
{
    char board[MAX_D][MAX_D];
    struct Node *next; //used for the fringe (queue), linked list based
    struct Node *prev; //refers to a node's singular parent
    int bX;
    int bY;    
};

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
    //direction is direction of movement of blank tile
    char temp;
    int bX = node->bX;
    int bY = node->bY;
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

void makeSameState(struct Node *node1, struct Node *node2)
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

/**********************************************************************************
 Queue data structure implementation (and related methods, of course)
 This queue only uses the next reference available to every struct Node,
 it does not use a separate linked list.
 *********************************************************************************/

struct Queue //implementation of linked list, but JUST with structs.      
{
    struct Node *head;
    struct Node *tail;
    int numNodes; // num of nodes in the queue
};


struct Queue newQueue()
{
    struct Queue q;
    q.numNodes = 0;
    q.head = NULL;
    q.tail = NULL;
    return q;
}

int isEmpty(struct Queue *queue)
{
    return (queue->numNodes == 0);
}

struct Node* dequeue(struct Queue *queue)
{
    struct Node *node;
    if (queue->head != NULL)
    {
        node = queue->head;
        queue->head = node->next;
        queue->numNodes--;
    }
    if (isEmpty(queue))
    {
        queue->head = NULL;
        queue->tail = NULL;
    }
    return node;
}

void enqueue(struct Queue *queue, struct Node *node) //Refactor
{
    if (isEmpty(queue))
    {
        queue->head = node;  
    }
    else
    {
        queue->tail->next = node;
    }
    queue->tail = node;
    node->next = NULL;
    queue->numNodes++;
}


void successorHelper(struct Queue *fringe, struct Node *node, enum swapDir direction)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    makeSameState(node, newNode);
    swapTile(newNode, direction);
    newNode->prev = node;
    enqueue(fringe, newNode);
}

void addSuccessorsToFringe(struct Queue *fringe, struct Node *node) // this was the culprit
{
    int bY = node->bY;
    int bX = node->bX;
    if (bY >= 0 && bY < MAX_D-1)
    {
        successorHelper(fringe, node, down);
    }

    if (bY > 0 && bY <= MAX_D-1)
    {
        successorHelper(fringe, node, up);
    }

    if (bX >= 0 && bX < MAX_D-1)
    {
        successorHelper(fringe, node, right);
    }

    if (bX > 0 && bX <= MAX_D-1)
    {   
        successorHelper(fringe, node, left);
    }
}

/***************************************************************************************
 Contains a 3-d array consisting of 1-100 board states
 **************************************************************************************/
struct Path
{
    int size;
    char boardStates[MAX_PATH][MAX_D][MAX_D];
};

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

struct Explored
{
    struct Node **uniqueNodes; //should be 362880
    int numStored;
};

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

int tallyLessThan(char state[MAX_D][MAX_D], int startPos, int numTiles) // helper function for findPermPos
{

    int tally = 0;
    int initX = startPos % MAX_D;
    int initY = startPos / MAX_D; // was floor
    int i, x, y;
    char checkVal = state[initY][initX];

    for (i = startPos + 1; i < numTiles; i++)
    {
        x = i % MAX_D;
        y = i / MAX_D; // was floor

        // separate check for blankChar, since arbitrarily defined, might be lexicographically greater than checkVal,
        // but needs to be treated as though it were '0'
        if (state[y][x] == blankChar || state[y][x] < checkVal)
        {
            tally++;
        } 
    }
    return tally;
}

// Effectively finds what position the state would be in if all 9! permutations were sorted in a container.
// Note: all 9! permutations, NOT the 9!/2 possible states from a given starting position.
int findPermPos(char state[MAX_D][MAX_D]) 
{
// with thanks to Gareth Rees here: https://stackoverflow.com/questions/12146910/finding-the-lexicographic-index-of-a-permutation-of-a-given-array
// post clarified an issue I had with a previous recursive implementation
    int pos = 0;
    int index = 0;
    
    while (pos < NUM_TILES)
    {
        index += factorial(NUM_TILES-1-pos) * tallyLessThan(state, pos, NUM_TILES);
        pos++;
    }
    return index;
}

void garbageCollection(struct Explored *explored, int exploredSize, struct Queue *queue)
{
    int i;
    int numLeft = explored->numStored;
    struct Node *node = queue->head;
    struct Node *temp;

    //to free the fringe
    while (node != NULL)
    {
        temp = node;
        node = node->next;
        free(temp);
    }

    // to free the explored container
    for (i = 0; i < exploredSize && numLeft > 0; i++)
    {
        if (explored->uniqueNodes[i] != NULL)
        {
            free(explored->uniqueNodes[i]);
            explored->numStored--;
        }
    }
    free(explored->uniqueNodes);
}


int main(int argc, char* argv[])
{   
    clock_t tAfterSearch, tBeforeSearch, tPathBegin, tPathEnd, tBeforeGarbCollect, tAfterGarbCollect;
    //clock_t begin, end;
    int numUniqueStates = 0;
    int numTotalStates = 0;
    int solutionFound = 0;
    int nodeStatePos = 0;
    double timeSearch, timePath, timeGarbageCollect;

    tBeforeSearch = clock();

    int gStatePos = findPermPos(gState);

    struct Explored explored = newExplored(PERMUTATIONS);
    struct Queue fringe = newQueue();
    struct Node *initialNode = makeInitialState();
    enqueue(&fringe, initialNode);

    struct Node *node;
    while (!isEmpty(&fringe))
    {
        node = dequeue(&fringe);
        numTotalStates++;
        
        // asymptotically, for every 2.66 states seen, one is unique. So about 37.6% of the time, the inner check will also be completed.
        // Therefore makes sense to store the permutation position of the node.
        nodeStatePos = findPermPos(node->board); 

        if (!inExplored(&explored, node, nodeStatePos))
        {
            numUniqueStates++;

            if (nodeStatePos == gStatePos) // inner check
            {
                solutionFound = 1;
                tAfterSearch = clock(); 
                tPathBegin = clock();
                printf("Solution found!\n");

                struct Path path = newPath();
                makePath(&path, node); printPath(&path);
                tPathEnd = clock();
                
                break;
            }
            addSuccessorsToFringe(&fringe, node);
            appendBoard(&explored, node, findPermPos(node->board));
        }

        else
        {
            free(node);
        }
    }
    tAfterSearch = clock();
    timeSearch = ((double) (tAfterSearch-tBeforeSearch)/ CLOCKS_PER_SEC);
    printf("tPathEnd: %f tPathBegin: %f\n", ((double) (tPathEnd/CLOCKS_PER_SEC)), ((double) (tPathBegin/CLOCKS_PER_SEC)) );
    timePath = ((double) (tPathEnd - tPathBegin)/ CLOCKS_PER_SEC);

    if(!solutionFound) printf("No solution found.\n");
    printf("Number of unique states searched: %d\n", numUniqueStates);
    printf("Number of total states searched: %d\n", numTotalStates);
    printf("The search for the solution took %f seconds.\n", timeSearch);
    printf("Putting together and showing the path took %f seconds.\n", timePath);
    
    tBeforeGarbCollect = clock();   
    garbageCollection(&explored, PERMUTATIONS, &fringe);
    tAfterGarbCollect = clock();

    timeGarbageCollect = ((double) (tAfterGarbCollect - tBeforeGarbCollect) / CLOCKS_PER_SEC);
    printf("Garbage collection took %f seconds.\n",timeGarbageCollect);
    //printf("Total time: %f\n", ((double) ((end - begin) / CLOCKS_PER_SEC)));
    return 0;   
}

//gcc -static -g -o 8TileTest6.01 8TileTest6.01.c
//valgrind -s --show-leak-kinds=all --leak-check=full --verbose ./8TileTest6.01



/* Rough structure:

function search(initialState, goalStates)
{
    fringe = [new node from initialState]
    explored=[]
    while (fringe not empty)
        node = fringe.remove()
        if node.state not in explored
            if node.state in goalStates report SUCCESS
            fringe += node.successors()
            explored +=node.state
    report FAILURE
}
*/



