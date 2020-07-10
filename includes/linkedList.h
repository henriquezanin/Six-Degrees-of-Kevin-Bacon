#ifndef __linkedList__
#define __linkedList__

#include <utils.h>

typedef struct listElement{
    struct listElement *next;
    int id;
    void *element;
}listElement;

typedef struct list{
    listElement *first;
    int nElements;
}List;

List *newList();
void *removeElementById(int, List *);
Error *addFirst(int , void *, List *);
Error *addLast(int , void *, List *);
int removeFirst(List *, Error *);
int removeLast(List *, Error *);
void **freeList(List *);
void *getElement(int, List *);
int *getAllIdElements(List *);
int getListSize(List *);
int getElementIDbyPosition(int , List *, Error *);

#endif