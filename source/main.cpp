#include <stdlib.h>

#include "stack.h"
#include "mem.h"


int main() {

    ProtectedStack stack;

    if (initialize(&stack) != NO_ERROR) return 1;
    printStack(&stack);
    push(&stack, 5);
    push(&stack, 22848);
    push(&stack, 85678);
    push(&stack, 9);
    push(&stack, 983);
    push(&stack, 0);
    push(&stack, -156);
    push(&stack, 346);
    push(&stack, 898652);
    push(&stack, -57676);


    printStack(&stack);

    push(&stack, 993);
    push(&stack, -445);
    push(&stack, 877);
    push(&stack, 44);
    push(&stack, -99);
    push(&stack, 5);
    push(&stack, 22848);
    push(&stack, 85678);
    push(&stack, 9);
    push(&stack, 983);
    push(&stack, 0);
    push(&stack, -156);
    *(stack.stack.data + 24) = 10;

    push(&stack, 346);
    push(&stack, 898652);
    push(&stack, -57676);
    push(&stack, 993);
    push(&stack, -445);
    push(&stack, 877);
    push(&stack, 44);
    push(&stack, -99);

    printStack(&stack);

    StackElem xdd;

    pop(&stack, &xdd);
    printf("Wowey: %d\n", xdd);
    
    pop(&stack, &xdd);
    printf("Wowey2: %d\n", xdd);
    
    pop(&stack, &xdd);
    printf("Wowey3: %d\n", xdd);
    
    pop(&stack, &xdd);
    printf("Wowey4: %d\n", xdd);
    
    printStack(&stack);

    *(stack.stack.data + 10) = 10;

    pop(&stack, NULL);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    pop(&stack, &xdd);
    *(stack.stack.data) = 10;
    pop(&stack, &xdd);
    
    printStack(&stack);

    return 0;
}
