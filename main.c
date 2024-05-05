#include <stdio.h>

#include "global/DL_list/list.h"
#include "global/SL_list/list.h"
#include "global/stack/stack.h"
#include "global/vector/vector.h"

int main()
{
    int x = 5;
    int y = 10;
    int z = 15;
    // Vector
    printf("Vector\n");
    T_Vector vector = T_VECTOR_NEW(int);
    t_vector_push_back(&vector, &x);
    t_vector_push_back(&vector, &y);
    t_vector_push_back(&vector, &z);
    T_VECTOR_FOR_EACH(iter, vector)
    {
        printf("%d ", T_VECTOR_ITERATOR_VALUE_AS(int, iter));
    }
    t_vector_destroy(&vector);
    printf("\n");
    // Stack
    printf("Stack\n");
    T_Stack stack = T_STACK_NEW(int);
    t_stack_push(&stack, &x);
    t_stack_push(&stack, &y);
    t_stack_push(&stack, &z);
    while (t_stack_isEmpty(&stack) != 1)
    {
        printf("%d ", T_STACK_TOP(int, stack));
        t_stack_pop(&stack);
    }
    t_stack_destroy(&stack);
    printf("\n");
    /// Singly Linked List
    printf("SL_list\n");
    T_SL_List sl_list = T_SL_LIST_NEW(int);
    t_SL_list_insertAtEnd(&sl_list, &x);
    t_SL_list_insertAt(&sl_list, &y, 1);
    t_SL_list_insertAt(&sl_list, &z, sl_list.size);
    struct T_SL_Node *sl_current = sl_list.first;
    while (sl_current != NULL)
    {
        printf("%d ", T_SL_LIST_NODE_VALUE_AS(int, sl_current));
        sl_current = sl_current->next;
    }
    t_SL_list_destroy(&sl_list);
    printf("\n");
    // Doubly Linked List
    printf("DL_list\n");
    T_DL_List dl_list = T_DL_LIST_NEW(int);
    t_DL_list_insertAtEnd(&dl_list, &x);
    t_DL_list_insertAt(&dl_list, &y, 1);
    t_DL_list_insertAt(&dl_list, &z, dl_list.size);
    struct T_DL_Node *dl_current = dl_list.first;
    while (dl_current != NULL)
    {
        printf("%d ", T_DL_LIST_NODE_VALUE_AS(int, dl_current));
        dl_current = dl_current->next;
    }
    t_DL_list_destroy(&dl_list);
    printf("\n");

    return 0;
}