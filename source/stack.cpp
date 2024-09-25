#include "stack.h"

const double RESIZE_COEFF = 1.41421356;
const double MIN_STACK_SIZE = 8;

int stackInit(Stack* stack){
    stack->capacity = MIN_STACK_SIZE;
    stack->size = 0;
    stack->data = (StackElem*)calloc(stack->capacity, sizeof(StackElem));
    if (stack->data == NULL) {
        printf("Error: enable to init memory\n");
        return 1;
    }
    return 0;
}

int stackDestroy(Stack* stack){
    free(stack->data);
    return 0;
}

int stackPush(Stack* stack, StackElem elem){
    ++stack->size;
    if (checkStack(stack) != 0) return 1;
    *(stack->data + (stack->size - 1)) = elem;
    return 0;
}

StackElem stackPop(Stack* stack){
    if (stack->size == 0) {
        printf("Stack is empty\n");
        return NULL;
    }
    StackElem elem = *(stack->data + (stack->size - 1));
    --stack->size;
    if (checkStack(stack) != 0) return NULL;
    return elem;
}

int checkStack(Stack* stack){
    if (stack->size > stack->capacity) {
        stack->data = (StackElem*)recalloc(stack->data, stack->capacity * sizeof(StackElem), (stack->size * RESIZE_COEFF) * sizeof(StackElem));
        stack->capacity = stack->size * RESIZE_COEFF;
        if (stack->data == NULL) return 1;
    }
    if (max(stack->size * RESIZE_COEFF, MIN_STACK_SIZE) < stack->capacity) {
        stack->data = (StackElem*)recalloc(stack->data, stack->capacity * sizeof(StackElem), max(stack->size, MIN_STACK_SIZE) * sizeof(StackElem));
        stack->capacity = max(stack->size, MIN_STACK_SIZE);
        if (stack->data == NULL) return 1;
    }
    return 0;
}

void printStackData(Stack* stack) {
    printf("Stack [0x%p]\n", stack);
    printf("Size = %d\n", stack->size);
    printf("Capacity = %d\n", stack->capacity);
    printf("Data [0x%p]\n", stack->data);

    for (int i = 0; i < stack->size; ++i) {
        printf("[%d] = %d\n", i, *(stack->data + i));
    }
    for (int i = stack->size; i < stack->capacity; ++i) {
        printf("*[%d] = %d\n", i, *(stack->data + i));
    }
}