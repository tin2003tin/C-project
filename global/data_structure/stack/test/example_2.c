#include <stdio.h>

#include "global/data_structure/stack/stack.h"

int main()
{
    T_Stack stack = T_STACK_NEW(T_Vector);
    T_Vector vector1 = T_VECTOR_NEW(int);
    T_Vector vector2 = T_VECTOR_NEW(int);
    for (size_t i = 0; i < 10; i++)
    {
        t_vector_push_back(&vector1, &i);
    }
    for (size_t i = 0; i < 5; i++)
    {
        t_vector_push_back(&vector2, &i);
    }
    printf("size of vector1: %ld\n", t_vector_get_size(&vector1));
    for (size_t i = 0; i < t_vector_get_size(&vector1); i++)
    {
        printf("%d ", T_VECTOR_GET_VALUE_AS(int, &vector1, i));
    }
    printf("\n");

    printf("size of vector2: %ld\n", t_vector_get_size(&vector2));
    for (size_t i = 0; i < t_vector_get_size(&vector2); i++)
    {
        printf("%d ", T_VECTOR_GET_VALUE_AS(int, &vector2, i));
    }
    printf("\n");

    T_Vector clone1 = t_vector_clone(&vector1);
    T_Vector clone2 = t_vector_clone(&vector2);

    t_stack_push(&stack, &clone1);
    t_stack_push(&stack, &clone2);
    t_vector_destroy(&vector1);
    t_vector_destroy(&vector2);
    T_Vector top = *(T_Vector *)t_stack_peek(&stack);
    printf("\n");
    printf("Top: \n");
    printf("size of top: %ld\n", t_vector_get_size(&top));
    for (size_t i = 0; i < t_vector_get_size(&top); i++)
    {
        printf("%d ", T_VECTOR_GET_VALUE_AS(int, &top, i));
    }
    printf("\n");
    printf("Pop: \n");
    t_vector_destroy(&top);
    t_stack_pop(&stack);
    printf("Top: \n");
    top = *(T_Vector *)t_stack_peek(&stack);
    printf("size of top: %ld\n", t_vector_get_size(&top));
    for (size_t i = 0; i < t_vector_get_size(&top); i++)
    {
        printf("%d ", T_VECTOR_GET_VALUE_AS(int, &top, i));
    }
    printf("\n");
    printf("Pop: \n");
    t_vector_destroy(&top);
    t_stack_pop(&stack);
    void *newTop = t_stack_peek(&stack);
    if (newTop == NULL)
    {
        printf("The stack is empty now!\n");
    }
    t_stack_destroy(&stack);
    return 0;
}