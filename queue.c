/**********************************************************************************
 Queue data structure implementation (and related methods, of course)
 This queue only uses the next reference available to every struct Node,
 it does not use a separate linked list.
 *********************************************************************************/

#include "queue.h"
#include "node.h"
#include "stdlib.h"

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
    // Does not check initially to see if queue is empty, assumed valid use case
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

void addSuccessorsToFringe(struct Queue *fringe, struct Node *node)
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