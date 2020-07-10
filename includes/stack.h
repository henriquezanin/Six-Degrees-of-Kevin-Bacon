#ifndef __STACK__
#define __STACK__
#include <linkedList.h>

typedef List Stack;
Stack *newStack();
Error *push(int , Stack *);
int pop(Stack *, Error *);
unsigned char stackIsEmpty(Stack *);
void freeStack(Stack *);
int getStackTop(Stack *, Error *);

#endif