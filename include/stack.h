#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "mem.h"

#define max(A, B) ((A) > (B) ? (A) : (B))

typedef int StackElem;

struct Stack {
    StackElem* data;
    int size;
    int capacity;
};

int stackInit(Stack* stack);

int stackDestroy(Stack* stack);

int stackPush(Stack* stack, StackElem elem);

StackElem stackPop(Stack* stack);

int checkStack(Stack* stack);

void printStackData(Stack* stack);

#endif