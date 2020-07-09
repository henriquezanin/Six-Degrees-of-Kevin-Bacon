#ifndef __QUEUE__
#define __QUEUE__
#include <linkedList.h>

typedef List Queue;
Queue *newQueue();
Error *enqueue(int , Queue *);
int dequeue(Queue *, Error *);
unsigned char queueIsEmpty(Queue *);
void freeQueue(Queue *);

#endif