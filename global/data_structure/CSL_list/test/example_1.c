#include <stdio.h>

#include "global/data_structure/CSL_list/CSL_list.h"

int main()
{
    T_CSL_List list = T_CSL_LIST_NEW(int);
    int x = 10;
    t_CSL_list_insertAtEnd(&list, &x);
    x = 20;
    t_CSL_list_insertAtEnd(&list, &x);
    x = 30;
    t_CSL_list_insertAtEnd(&list, &x);
    x = 40;
    t_CSL_list_insertAtBegin(&list, &x);
    x = 99;
    t_CSL_list_insertAt(&list, &x, 2);
    x = 555;
    t_CSL_list_insertAt(&list, &x, list.size + 2);
    struct T_CSL_Node *current = list.first;
    printf("After Inserting\n");
    printf("Size: %ld\n", list.size);
    do
    {
        printf("%d ", T_CSL_LIST_NODE_VALUE_AS(int, current));
        current = current->next;
    } while (current != list.first);
    printf("\n");
    printf("10 Index\n");
    printf("Size: %ld\n", list.size);
    current = list.first;
    int index = 10;
    for (int i = 0; i < index; i++)
    {
        printf("%d ", T_CSL_LIST_NODE_VALUE_AS(int, current));
        current = current->next;
    }
    printf("\n");
    t_CSL_list_deleteAtBegin(&list);
    t_CSL_list_deleteAtEnd(&list);
    t_CSL_list_deleteAt(&list, 1);

    current = list.first;
    printf("After Deleting\n");
    printf("Size: %ld\n", list.size);
    do
    {
        printf("%d ", T_CSL_LIST_NODE_VALUE_AS(int, current));
        current = current->next;
    } while (current != list.first);

    printf("\n");
    t_CSL_list_clear(&list);
    printf("After Clear\n");
    printf("Size: %ld\n", list.size);
    return 0;
}