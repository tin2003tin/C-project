#include <stdio.h>

#include "global/data_structure/stack/stack.h"

int main()
{
    T_Stack stack = T_STACK_NEW(int);
    int x = 5;
    t_stack_push(&stack, &x);
    int y = 111;
    t_stack_push(&stack, &y);
    printf("size: %ld\n", t_stack_get_size(&stack));
    printf("%d\n", T_STACK_TOP(int, &stack));
    t_stack_pop(&stack);
    printf("peek: %d\n", *(int *)t_stack_peek(&stack));
    t_stack_clear(&stack);

    t_stack_destroy(&stack);
    return 0;
}