#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "mem.h"
#include "errorTypes.h"

#define max(A, B) ((A) > (B) ? (A) : (B))

typedef int StackElem;

struct Stack {
    char* data;
    int size;
    int capacity;
    uint64_t hash;
};

struct ProtectedStack{
    Stack stack;
    bool isInit = false;
};

stackErrorType initialize(ProtectedStack* pstack);

stackErrorType destroy(ProtectedStack* pstack);

stackErrorType push(ProtectedStack* pstack, StackElem elem);

stackErrorType pop(ProtectedStack* pstack, StackElem* elem);

stackErrorType printStack(const ProtectedStack* pstack);

//int getsize(ProtectedStack* pstack);


stackErrorType stackInit(Stack* stack);

stackErrorType stackDestroy(Stack* stack);

stackErrorType stackPush(Stack* stack, StackElem elem);

stackErrorType stackPop(Stack* stack, StackElem* elem);

stackErrorType updateStackCapacity(Stack* stack);

void printStackData(const Stack* stack);

uint64_t calcHash(const Stack* stack);

stackErrorType checkHash(const Stack* stack);

stackErrorType checkCanary(const Stack* stack);

stackErrorType checkStack(const ProtectedStack* pstack);

#endif