#include "breadthFirstSearch.h"
#include "node.h"
#include "queue.h"
#include "explored.h"
#include "path.h"
#include "constants.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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

int breadthFirstSearch()
{
    int numUniqueStates = 0;
    int numTotalStates = 0;
    int solutionFound = 0;
    int nodeStatePos = 0;

    populateFactorialResults(factorialResults);
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
                struct Path path = newPath();
                makePath(&path, node); 
                printPath(&path);

                if (!TIMING_MODE){
                    printf("Number of unique states searched: %d\n", numUniqueStates);
                    printf("Number of total states searched: %d\n", numTotalStates);
                }
                
                garbageCollection(&explored, PERMUTATIONS, &fringe); 
                return 1;
            }
            addSuccessorsToFringe(&fringe, node);
            appendBoard(&explored, node, findPermPos(node->board));
        }

        else
        {
            free(node);
        }
    }
    if (!TIMING_MODE){
        printf("No path between start and end states found.\n");
        printf("Number of unique states searched: %d\n", numUniqueStates);
        printf("Number of total states searched: %d\n", numTotalStates);
    }

    garbageCollection(&explored, PERMUTATIONS, &fringe);
}

void runNTimes(int n)
{
    int numIterations = n;
    int i = 0;
    double cumulativeTime = 0;
    clock_t begin, end;
    while (i++ < numIterations)
    {
      begin = clock();
      breadthFirstSearch();
      end = clock();

      cumulativeTime += ((double) (end - begin)/ CLOCKS_PER_SEC);
      //printf("iteration: %d\r", i);
      //fflush(stdout);
    }
    printf("numIterations: %d tTotal: %f seconds tAverage: %3.3f ms\n", numIterations, cumulativeTime, cumulativeTime/numIterations * 1000);
}