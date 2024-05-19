#include <stdio.h>

#include "global/data_structure/DL_list/DL_list.h"

int main()
{
    T_DL_List list = T_DL_LIST_NEW(int);
    int x = 10;
    t_DL_list_insertAtEnd(&list, &x);
    x = 20;
    t_DL_list_insertAtEnd(&list, &x);
    x = 30;
    t_DL_list_insertAtEnd(&list, &x);
    x = 40;
    t_DL_list_insertAtBegin(&list, &x);
    x = 99;
    t_DL_list_insertAt(&list, &x, 2);
    struct T_DL_Node *current = list.first;
    printf("After Inserting\n");
    printf("Size: %ld\n", list.size);
    while (current != NULL)
    {
        printf("%d ", T_DL_LIST_NODE_VALUE_AS(int, current));
        current = current->next;
    }
    printf("\n");
    t_DL_list_deleteAtBegin(&list);
    t_DL_list_deleteAtEnd(&list);
    t_DL_list_deleteAt(&list, 1);

    current = list.first;
    printf("After Deleting\n");
    printf("Size: %ld\n", list.size);
    while (current != NULL)
    {
        printf("%d ", T_DL_LIST_NODE_VALUE_AS(int, current));
        current = current->next;
    }

    printf("\n");
    t_DL_list_clear(&list);
    printf("After Clear\n");
    printf("Size: %ld\n", list.size);
    return 0;
}