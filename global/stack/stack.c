#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define T_STACK_DEFAULT_SIZE 0
#define T_STACK_DEFAULT_CAPACITY 1

#define T_STACK_GROW_COND 100
#define T_STACK_GROW_RATE 200

#define T_STACK_SHRINK_COND 0
#define T_STACK_SHRINK_RATE 0

#define T_STACK_ERROR 1
#define T_STACK_SUCCESS 0

T_Stack t_stack_init(size_t typeSize)
{
    return t_stack_custom_init(typeSize, T_STACK_DEFAULT_CAPACITY, T_STACK_GROW_COND, T_STACK_GROW_RATE, T_STACK_SHRINK_COND, T_STACK_SHRINK_RATE);
}
T_Stack t_stack_custom_init(size_t typeSize, size_t capacity, size_t growCond, size_t growRate, size_t shrinkCond, size_t shrinkRate)
{
    T_Stack stack;
    T_Vector vector = t_vector_custom_init(typeSize, capacity, growCond, growRate, shrinkCond, shrinkRate);
    if (vector.data == NULL)
    {
        exit(EXIT_FAILURE);
    }
    stack.vector = vector;
    return stack;
}
T_Stack t_stack_clone(const T_Stack *stack)
{
    assert(stack != NULL);
    T_Stack clone_stack;
    clone_stack.vector = t_vector_clone(&(stack->vector));
    return clone_stack;
}

void t_stack_destroy(T_Stack *stack)
{
    assert(stack != NULL);
    t_vector_destroy(&(stack->vector));
}

int t_stack_push(T_Stack *stack, void *element)
{
    assert(stack != NULL);
    if (stack == NULL)
    {
        printf("ERROR: Stack is null\n");
        return T_STACK_ERROR;
    }
    if (t_vector_push_back(&(stack->vector), element) == 1)
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
    if (t_vector_pop_back(&(stack->vector)) == 1)
    {
        return T_STACK_ERROR;
    }
    return T_STACK_SUCCESS;
}
int t_stack_isEmpty(const T_Stack *stack)
{
    assert(stack != NULL);
    return t_vector_get_size(&(stack->vector)) == 0;
}
size_t t_stack_get_size(const T_Stack *stack)
{
    assert(stack != NULL);
    return t_vector_get_size(&(stack->vector));
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

void *t_stack_peek(const T_Stack *stack)
{
    assert(stack != NULL);
    if (t_stack_isEmpty(stack))
    {
        printf("\x1B[31m"
               "Error: Stack is empty\n"
               "\x1B[0m");
        return NULL;
    }

    return t_vector_iter_at(&(stack->vector), t_vector_get_size(&(stack->vector)) - 1).pointer;
}
