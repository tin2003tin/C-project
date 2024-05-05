#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

T_Stack t_stack_init(size_t typeSize)
{
    T_Stack stack;
    stack.vector = t_vector_init(typeSize);
    return stack;
}

int t_stack_push(T_Stack *stack, void *element)
{
    assert(stack != NULL);
    if (stack == NULL)
    {
        printf("ERROR: Stack is null\n");
        return T_STACK_ERROR;
    }
    if (t_vector_push_back(&(stack->vector), element) == T_VECTOR_ERROR)
    {
        return T_STACK_ERROR;
    }
    return T_STACK_SUCCESS;
}
int t_stack_pop(T_Stack *stack)
{
    assert(stack != NULL);
    if (stack == NULL)
    {
        printf("ERROR: Stack is null\n");
        return T_STACK_ERROR;
    }
    if (t_stack_isEmpty(stack))
    {
        printf("Error: Stack is empty\n");
        return T_STACK_ERROR;
    }
    if (t_vector_pop_back(&(stack->vector)) == T_VECTOR_ERROR)
    {
        return T_STACK_ERROR;
    }
    return T_STACK_SUCCESS;
}
int t_stack_isEmpty(T_Stack *stack)
{
    assert(stack != NULL);
    return stack->vector.size == 0;
}
size_t t_stack_getSize(T_Stack *stack)
{
    assert(stack != NULL);
    return stack->vector.size;
}
int t_stack_clear(T_Stack *stack)
{
    assert(stack != NULL);
    if (stack == NULL)
    {
        printf("ERROR: Stack is null\n");
        return T_STACK_ERROR;
    }
    t_vector_clear(&(stack->vector));
    return T_STACK_SUCCESS;
}

void *t_stack_peek(T_Stack *stack)
{
    assert(stack != NULL);
    if (stack->vector.data == NULL)
    {
        printf("\x1B[31m"
               "Stack is null\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (t_stack_isEmpty(stack))
    {
        printf("\x1B[31m"
               "Error: Stack is empty\n"
               "\x1B[0m");
        return NULL;
    }
    return t_vector_get(&(stack->vector), stack->vector.size - 1);
}

void t_stack_destroy(T_Stack *stack)
{
    assert(stack != NULL);
    t_vector_destroy(&(stack->vector));
}