// include the other header files as required
#ifndef BFS
#define BFS

#include "queue.h"
#include "explored.h"

void garbageCollection(struct Explored *explored, int exploredSize, struct Queue *queue);
int breadthFirstSearch();
void runNTimes(int n);

#endif