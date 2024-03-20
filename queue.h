#ifndef QUEUE
#define QUEUE

#include "constants.h"
#include "node.h"

struct Queue //implementation of linked list, but JUST with structs.      
{
    struct Node *head;
    struct Node *tail;
    int numNodes; // num of nodes in the queue
};

struct Queue newQueue();
int isEmpty(struct Queue *queue);
struct Node* dequeue(struct Queue *queue);
void enqueue(struct Queue *queue, struct Node *node);
void successorHelper(struct Queue *fringe, struct Node *node, enum swapDir direction);
void addSuccessorsToFringe(struct Queue *fringe, struct Node *node);

#endif