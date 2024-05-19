#include <stdio.h>

#include "global/data_structure/SL_list/SL_list.h"

int main()
{
    T_SL_List list = T_SL_LIST_NEW(int);
    int x = 5;
    t_SL_list_insertAtEnd(&list, &x);
    x = 10;
    t_SL_list_insertAtEnd(&list, &x);
    x = 15;
    t_SL_list_insertAtEnd(&list, &x);
    x = 20;
    t_SL_list_insertAtEnd(&list, &x);
    x = 1;
    t_SL_list_insertAtBegin(&list, &x);
    x = 999;
    t_SL_list_insertAt(&list, &x, 3);
    t_SL_list_deleteAt(&list, 1);
    struct T_SL_Node *current = list.first;
    while (current != NULL)
    {
        printf("%d ", T_SL_LIST_NODE_VALUE_AS(int, current));
        current = current->next;
    }
    printf("\n");
    t_SL_list_clear(&list);
    t_SL_list_insertAt(&list, &x, 0);
    current = list.first;
    while (current != NULL)
    {
        printf("%d ", T_SL_LIST_NODE_VALUE_AS(int, current));
        current = current->next;
    }
    t_SL_list_destroy(&list);
    return 0;
}