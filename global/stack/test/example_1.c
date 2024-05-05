#include <stdio.h>

#include "../stack.h"

// gcc .\global\stack\test\example.c global/vector/vector.c global/stack/stack.c -o out/stack_example_1
int main()
{
    T_Stack stack = T_STACK_NEW(int);
    int x = 5;
    t_stack_push(&stack, &x);
    int y = 111;
    t_stack_push(&stack, &y);
    printf("size: %d\n", t_stack_getSize(&stack));
    printf("%d\n", T_STACK_TOP(int, stack));
    t_stack_pop(&stack);
    printf("peek: %d\n", *(int *)t_stack_peek(&stack));
    t_stack_clear(&stack);
  
    t_stack_destroy(&stack);
    return 0;
}