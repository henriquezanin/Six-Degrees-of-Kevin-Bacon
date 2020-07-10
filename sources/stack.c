#include <stdlib.h>
#include <stdio.h>
#include <linkedList.h>
#include <utils.h>
#include <stack.h>

Stack *newStack(){
    return (Stack*)newList();
}

Error *push(int elem, Stack *stack){
    return addLast(elem, NULL, (List*)stack);
}

int pop(Stack *stack, Error *err){
    if(!err){
        puts("pop: Uninitialized error");
        return -1;
    }
    int elem = removeLast((List *)stack, err);
    if(hasError(err))
        ErrorFormat("pop: Failed to remove stack element", err);
    return elem;
}

int getStackTop(Stack *stack, Error *err){
    if(!err){
        puts("getStackTop: Uninitialized error");
        return -1;
    }
    if(!stack){
        ErrorFormat("getStackTop: null stack", err);
        return -1;
    }
    if(!stack->nElements)
        return -1;
    return getElementIDbyPosition(stack->nElements-1, (List*)stack, err);
}

unsigned char stackIsEmpty(Stack *stack){
    return (stack->nElements) ? 0 : 1;
}

void freeStack(Stack *stack){
    freeList((List*)stack);
}