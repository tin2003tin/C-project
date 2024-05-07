#ifndef tin_STACK
#define tin_STACK
#include <stddef.h>
#include "../vector/vector.h"

#define T_STACK_ERROR 1
#define T_STACK_SUCCESS 0

// Stack Type
typedef struct T_Stack
{
    T_Vector vector;
} T_Stack;

// Constructor and Destructor
T_Stack t_stack_init(size_t typeSize);
T_Stack t_stack_custom_init(size_t typeSize, size_t capacity, size_t growCond, size_t growRate, size_t shrinkCond, size_t shrinkRate);
T_Stack t_stack_clone(const T_Stack *stack);
void t_stack_destroy(T_Stack *stack);

// Get Stack details
int t_stack_isEmpty(const T_Stack *stack);
size_t t_stack_get_size(const T_Stack *stack);
void *t_stack_peek(const T_Stack *stack);

// Add & remove item
int t_stack_push(T_Stack *stack, void *element);
int t_stack_pop(T_Stack *stack);

// Memory management
int t_stack_clear(T_Stack *stack);

// Utility macros
#define T_STACK_NEW(type) t_stack_init(sizeof(type))
#define T_STACK_TOP(type, stack) *(type *)(t_stack_peek(stack))
#endif
