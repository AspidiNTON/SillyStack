#include <stdlib.h>
#include <stack.h>
#include <mem.h>


int main() {
    Stack stack;
    if (stackInit(&stack) != 0) return 0;
    stackPush(&stack, 5);
    stackPush(&stack, 22848);
    stackPush(&stack, 85678);
    stackPush(&stack, 9);
    stackPush(&stack, 983);
    stackPush(&stack, 0);
    stackPush(&stack, -156);
    stackPush(&stack, 346);
    stackPush(&stack, 898652);
    stackPush(&stack, -57676);
    stackPush(&stack, 993);
    stackPush(&stack, -445);
    stackPush(&stack, 877);
    stackPush(&stack, 44);
    stackPush(&stack, -99);
    stackPush(&stack, 5);
    stackPush(&stack, 22848);
    stackPush(&stack, 85678);
    stackPush(&stack, 9);
    stackPush(&stack, 983);
    stackPush(&stack, 0);
    stackPush(&stack, -156);
    stackPush(&stack, 346);
    stackPush(&stack, 898652);
    stackPush(&stack, -57676);
    stackPush(&stack, 993);
    stackPush(&stack, -445);
    stackPush(&stack, 877);
    stackPush(&stack, 44);
    stackPush(&stack, -99);

    printStackData(&stack);


    return 0;
}
