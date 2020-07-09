#include <stdlib.h>
#include <stdio.h>
#include <linkedList.h>
#include <utils.h>
#include <queue.h>

Queue *newQueue(){
    return (Queue*)newList();
}

Error *enqueue(int elem, Queue *queue){
    return addFirst(elem, NULL, (List*)queue);
}

int dequeue(Queue *queue, Error *err){
    if(!err){
        puts("dequeue: Uninitialized error");
        return -1;
    }
    int elem = removeLast((List *)queue, err);
    if(hasError(err))
        ErrorFormat("dequeue: Failed to remove queue element", err);
    return elem;
}

unsigned char queueIsEmpty(Queue *queue){
    return (queue->nElements) ? 0 : 1;
}

void freeQueue(Queue *queue){
    freeList((List*)queue);
}