#include "stack.h"

typedef uint64_t canary_t;

const double RESIZE_COEFF = 1.4;
const double MIN_STACK_SIZE = 8;
const canary_t CANARY = 133769420;

stackErrorType initialize(ProtectedStack* pstack) {
    if (pstack->isInit) {
        printErr("Error: stack already initialized\n");
        return REINITIALISATION_ERROR;
    }
    stackErrorType err = stackInit(&pstack->stack);
    if (err == NO_ERROR) pstack->isInit = true;
    return err;
}

/*int getsize(ProtectedStack* pstack) {
    return pstack->stack.size;
}*/

stackErrorType destroy(ProtectedStack* pstack) {
    if (pstack->isInit) {
        stackDestroy(&pstack->stack);
        pstack->isInit = false;
    } else {
        printErr("Error: stack is unitialized\n");
        return DESTRUCTION_ERROR;
    }
    return NO_ERROR;
}

stackErrorType push(ProtectedStack* pstack, StackElem elem) {
    checkStack(pstack);
    return stackPush(&pstack->stack, elem);
}

stackErrorType pop(ProtectedStack* pstack, StackElem* elem) {
    if (elem == NULL) {
        printErr("Error: nullptr recieved\n");
        return NULLPTR_ERROR;
    }
    checkStack(pstack);
    return stackPop(&pstack->stack, elem);
}

stackErrorType stackInit(Stack* stack){
    stack->capacity = MIN_STACK_SIZE;
    stack->size = 0;
    stack->data = (char*)calloc(stack->capacity * sizeof(StackElem) + sizeof(CANARY) * 2, 1);
    *(canary_t*)stack->data = CANARY;
    *(canary_t*)(stack->data + stack->capacity * sizeof(StackElem) + sizeof(CANARY)) = CANARY;
    if (stack->data == NULL) {
        printErr("Error: unable to init memory\n");
        return INITIALISATION_ERROR;
    }
    stack->hash = calcHash(stack);
    return NO_ERROR;
}

stackErrorType stackDestroy(Stack* stack){
    memset(stack->data, 0, stack->capacity * sizeof(StackElem) + 2 * sizeof(CANARY));
    free(stack->data);
    stack->data = NULL;
    return NO_ERROR;
}

stackErrorType stackPush(Stack* stack, StackElem elem){
    ++stack->size;
    stackErrorType err = updateStackCapacity(stack);
    if (err != NO_ERROR) return err;
    *(StackElem*)((stack->data + sizeof(StackElem) * (stack->size - 1) + sizeof(CANARY))) = elem;
    stack->hash = calcHash(stack);
    return NO_ERROR;
}

stackErrorType stackPop(Stack* stack, StackElem* elem){
    if (stack->size == 0) {
        printErr("Error: stack is empty\n");
        return EMPTY_ERROR;
    }
    assert(checkHash(stack) != 1);
    *elem = *(StackElem*)(stack->data + sizeof(StackElem) * (stack->size - 1) + sizeof(CANARY));
    --stack->size;
    stackErrorType err = updateStackCapacity(stack);
    if (err != NO_ERROR) return err;
    stack->hash = calcHash(stack);
    return NO_ERROR;
}

stackErrorType updateStackCapacity(Stack* stack){
    if (stack->size > stack->capacity) {
        void* tmp = recalloc(stack->data, stack->capacity * sizeof(StackElem) + sizeof(CANARY) * 2, (stack->size * RESIZE_COEFF) * sizeof(StackElem) + sizeof(CANARY) * 2);
        if (tmp == NULL) {
            printErr("Error: unable to recalloc stack\n");
            return RESIZE_ERROR;
        }
        stack->data = (char*)tmp;
        stack->capacity = stack->size * RESIZE_COEFF;
        *(canary_t*)(stack->data + stack->capacity * sizeof(StackElem) + sizeof(CANARY)) = CANARY;
    }
    if (max(stack->size * RESIZE_COEFF, MIN_STACK_SIZE) < stack->capacity) {
        void* tmp = recalloc(stack->data, stack->capacity * sizeof(StackElem) + sizeof(CANARY) * 2, max(stack->size, MIN_STACK_SIZE) * sizeof(StackElem) + sizeof(CANARY) * 2);
        if (tmp == NULL) {
            printErr("Error: unable to recalloc stack\n");
            return RESIZE_ERROR;
        }
        stack->data = (char*)tmp;
        stack->capacity = max(stack->size, MIN_STACK_SIZE);
        *(canary_t*)(stack->data + stack->capacity * sizeof(StackElem) + sizeof(CANARY)) = CANARY;
    }
    return NO_ERROR;
}

stackErrorType printStack(const ProtectedStack* pstack) {
    stackErrorType err = checkStack(pstack);
    if (err != NO_ERROR) return err;
    printStackData(&pstack->stack);
    return NO_ERROR;
}

void printStackData(const Stack* stack) {
    printf("Stack [0x%p]\n", stack);
    printf("Size = %d\n", stack->size);
    printf("Capacity = %d\n", stack->capacity);
    printf("Data [0x%p]\n", stack->data);
    printf("Hash = %llu\n", stack->hash);
    printf("Canary: %llu\n", *(canary_t*)stack->data);
    for (int i = 0; i < stack->size; ++i) {
        printf("[%d] = %d\n", i, *(StackElem*)(stack->data + i * sizeof(StackElem) + sizeof(CANARY)));
    }
    for (int i = stack->size; i < stack->capacity; ++i) {
        printf("*[%d] = %d\n", i, *(StackElem*)(stack->data + i * sizeof(StackElem) + sizeof(CANARY)));
    }
    printf("Canary: %llu\n", *(canary_t*)(stack->data + stack->capacity * sizeof(StackElem) + sizeof(CANARY)));
    putchar('\n');
}

uint64_t calcHash(const Stack* stack) {
    uint64_t hash = 5381;
    for (int i = 0; i < stack->size; ++i) {
        hash = hash * 33 ^ *(StackElem*)(stack->data + i * sizeof(StackElem) + sizeof(CANARY));
    }
    return hash;
}

stackErrorType checkHash(const Stack* stack) {
    if (calcHash(stack) != stack->hash) {
        printErr("Error: hash was modified\n");
        return HASH_ERROR;
    }
    return NO_ERROR;
}

stackErrorType checkCanary(const Stack* stack) {
    if (*(canary_t*)stack->data != CANARY) {
        printErr("Error: wrong left canary\n");
        return CANARY_ERROR;
    }
    if (*(canary_t*)(stack->data + stack->capacity * sizeof(StackElem) + sizeof(canary_t)) != CANARY) {
        printErr("Error: wrong right canary\n");
        return CANARY_ERROR;
    }
    return NO_ERROR;
}

stackErrorType checkStack(const ProtectedStack* pstack){
    if (!pstack->isInit) {
        printErr("Error: stack is unitialized\n");
        return UNINITIALIZED_STACK_ERROR;
    }
    if (pstack->stack.size > pstack->stack.capacity) {
        printErr("Error: size is bigger than capacity\n");
        return CAPACITY_ERROR;
    }
    if (checkCanary(&pstack->stack) != NO_ERROR) return CANARY_ERROR;
    if (checkHash(&pstack->stack) != NO_ERROR) return HASH_ERROR;
    return NO_ERROR;
}