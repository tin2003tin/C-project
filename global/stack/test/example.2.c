#include <stdio.h>

#include "../stack.h"

int main()
{
    T_Stack stack = T_STACK_NEW(T_Vector);
    T_Vector vector1 = T_VECTOR_NEW(int);
    T_Vector vector2 = T_VECTOR_NEW(int);
    T_Vector vector3 = T_VECTOR_NEW(int);
    int y = 10;

    t_stack_push(&stack, &vector1);
    t_stack_push(&stack, &vector2);
    t_vector_destroy(&vector1);
    T_Vector top = (T_STACK_TOP(T_Vector, stack));
    int x = 5;
    printf("%d\n", &top);
    t_vector_push_back(&top, &x);
    x = 10;
    t_vector_push_back(&top, &x);
    x = 15;
    t_vector_push_back(&top, &x);
    printf("Size: %d\n", top.size);
    for (size_t index = 0; index < top.size; index++)
    {
        printf("%d\n", T_VECTOR_GET_AS(int, top, index));
    }

    vector2.size = 3;
    printf("Size: %d\n", vector2.size);
    for (size_t index = 0; index < vector2.size; index++)
    {
        printf("%d\n", T_VECTOR_GET_AS(int, vector2, index));
    }
    // t_vector_destroy(&top);
    t_stack_pop(&stack);

    return 0;
}