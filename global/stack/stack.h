#ifndef tin_STACK
#define tin_STACK
#include <stddef.h>
#include "../vector/vector.h"

#define T_STACK_ERROR 1
#define T_STACK_SUCCESS 0

typedef struct
{
    T_Vector vector;
} T_Stack;

// contructor
T_Stack t_stack_init(size_t typeSize);
int t_stack_push(T_Stack *stack, void *element);
int t_stack_pop(T_Stack *stack);
int t_stack_isEmpty(T_Stack *stack);
size_t t_stack_getSize(T_Stack *stack);
int t_stack_clear(T_Stack *stack);
void *t_stack_peek(T_Stack *stack);
void t_stack_destroy(T_Stack *stack);

// utilities
#define T_STACK_NEW(type) t_stack_init(sizeof(type))
#define T_STACK_TOP(type, stack) *(type *)(t_stack_peek(&stack))
#endif
