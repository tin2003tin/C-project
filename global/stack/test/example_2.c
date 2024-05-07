#include <stdio.h>

#include "../stack.h"

int main()
{
    T_Stack stack = T_STACK_NEW(T_Vector);
    T_Vector vector1 = T_VECTOR_NEW(int);
    T_Vector vector2 = T_VECTOR_NEW(int);
    for (size_t i = 0; i < 10; i++)
    {
        t_vector_push_back(&vector1, &i);
    }
    printf("size of vector1: %d\n", t_vector_get_size(&vector1));
    for (size_t i = 0; i < t_vector_get_size(&vector1); i++)
    {
        printf("%d ", T_VECTOR_GET_VALUE_AS(int, &vector1, i));
    }
    printf("\n");

    T_Vector clone = t_vector_clone(&vector1);

    t_stack_push(&stack, &clone);
    t_vector_destroy(&vector1);
    T_Vector top = *(T_Vector *)t_stack_peek(&stack);
    printf("size of top: %d\n", t_vector_get_size(&top));
    for (size_t i = 0; i < t_vector_get_size(&top); i++)
    {
        printf("%d ", T_VECTOR_GET_VALUE_AS(int, &top, i));
    }
    printf("\n");

    return 0;
}