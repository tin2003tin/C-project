
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

T_DL_List t_DL_list_init(size_t typeSize)
{
    T_DL_List list;
    list.first = NULL;
    list.end = NULL;
    list.size = 0;
    list.typeSize = typeSize;
    return list;
}

int t_DL_list_insertAtEnd(T_DL_List *list, void *element)
{
    assert(list != NULL);
    if (list == NULL)
    {
        printf("\x1B[31m"
               "list is null\n"
               "\x1B[0m");
        return T_DL_LIST_ERROR;
    }
    struct T_DL_Node *newNode = _t_DL_list_nodeInit(list->typeSize);
    if (newNode == NULL)
    {
        return T_DL_LIST_ERROR;
    }
    memcpy(newNode->data, element, list->typeSize);

    if (list->first == NULL)
    {
        list->first = newNode;
    }
    else
    {
        list->end->next = newNode;
        newNode->previous = list->end;
    }

    list->end = newNode;
    list->size++;
    return T_DL_LIST_SUCCUESS;
}

int t_DL_list_insertAtBegin(T_DL_List *list, void *element)
{
    assert(list != NULL);
    if (list == NULL)
    {
        printf("\x1B[31m"
               "list is null\n"
               "\x1B[0m");
        return T_DL_LIST_ERROR;
    }
    struct T_DL_Node *newNode = _t_DL_list_nodeInit(list->typeSize);
    if (newNode == NULL)
    {
        return T_DL_LIST_ERROR;
    }
    memcpy(newNode->data, element, list->typeSize);
    if (list->first == NULL)
    {
        list->end = newNode;
    }
    else
    {
        list->first->previous = newNode;
        newNode->next = list->first;
    }
    list->first = newNode;
    list->size++;
    return T_DL_LIST_SUCCUESS;
}

int t_DL_list_insertAt(T_DL_List *list, void *element, size_t index)
{
    assert(list != NULL);

    if (index > list->size)
    {
        printf("\x1B[31m"
               "Index out of bounds. size: %zu\n"
               "\x1B[0m",
               list->size);
        return T_DL_LIST_ERROR;
    }
    if (index == 0)
    {
        return t_DL_list_insertAtBegin(list, element);
    }
    if (index == list->size)
    {
        return t_DL_list_insertAtEnd(list, element);
    }
    struct T_DL_Node *newNode = _t_DL_list_nodeInit(list->typeSize);
    if (newNode == NULL)
    {
        return T_DL_LIST_ERROR;
    }
    memcpy(newNode->data, element, list->typeSize);
    struct T_DL_Node *target = _t_DL_list_nodeAt(list, index - 1);
    struct T_DL_Node *next = target->next;

    target->next = newNode;
    newNode->previous = target;
    newNode->next = next;
    next->previous = newNode;

    list->size++;
    return T_DL_LIST_SUCCUESS;
}
int t_DL_list_deleteAtEnd(T_DL_List *list)
{
    assert(list != NULL);

    if (list->end == NULL)
    {
        printf("\x1B[31m"
               "list->end is null\n"
               "\x1B[0m");
        return T_DL_LIST_ERROR;
    }
    if (list->first == list->end)
    {
        free(list->end->data);
        free(list->end);
        list->first = NULL;
        list->end = NULL;
    }
    else
    {
        struct T_DL_Node *newEnd = list->end->previous;
        newEnd->next = NULL;
        free(list->end->data);
        free(list->end);
        list->end = newEnd;
    }
    list->size--;
    return T_DL_LIST_SUCCUESS;
}
int t_DL_list_deleteAtBegin(T_DL_List *list)
{
    assert(list != NULL);

    if (list->first == NULL)
    {
        printf("\x1B[31m"
               "list->end is null\n"
               "\x1B[0m");
        return T_DL_LIST_ERROR;
    }
    if (list->first == list->end)
    {
        free(list->end->data);
        free(list->end);
        list->first = NULL;
        list->end = NULL;
    }
    else
    {
        struct T_DL_Node *newFirst = list->first->next;
        newFirst->previous = NULL;
        free(list->first->data);
        free(list->first);
        list->first = newFirst;
    }
    list->size--;
    return T_DL_LIST_SUCCUESS;
}
int t_DL_list_deleteAt(T_DL_List *list, size_t index)
{
    assert(list != NULL);

    if (index >= list->size)
    {
        printf("\x1B[31m"
               "Index out of bounds. size: %zu\n"
               "\x1B[0m",
               list->size);
        return T_DL_LIST_ERROR;
    }
    if (list->first == NULL)
    {
        printf("\x1B[31m"
               "list->first is null\n"
               "\x1B[0m");
        return T_DL_LIST_ERROR;
    }
    if (index == 0)
    {
        return t_DL_list_deleteAtBegin(list);
    }
    if (index == list->size - 1)
    {
        return t_DL_list_deleteAtEnd(list);
    }
    struct T_DL_Node *target = _t_DL_list_nodeAt(list, index);
    struct T_DL_Node *previous = target->previous;
    struct T_DL_Node *next = target->next;
    free(target->data);
    free(target);
    previous->next = next;
    next->previous = previous;
    list->size--;
    return T_DL_LIST_SUCCUESS;
}

void *t_DL_list_getBegin(T_DL_List *list)
{
    struct T_DL_Node *target = _t_DL_list_nodeBegin(list);
    if (target->data == NULL)
    {
        return NULL;
    }
    return target->data;
}
void *t_DL_list_getEnd(T_DL_List *list)
{
    struct T_DL_Node *target = _t_DL_list_nodeEnd(list);
    if (target->data == NULL)
    {
        return NULL;
    }
    return target->data;
}
void *t_DL_list_getAt(T_DL_List *list, size_t index)
{
    struct T_DL_Node *target = _t_DL_list_nodeAt(list, index);
    if (target->data == NULL)
    {
        return NULL;
    }
    return target->data;
}
int t_DL_list_clear(T_DL_List *list)
{
    assert(list != NULL);

    if (list->first == NULL)
    {
        printf("\x1B[31m"
               "list->first is null\n"
               "\x1B[0m");
        return T_DL_LIST_ERROR;
    }
    struct T_DL_Node *current = list->first;
    while (current != NULL)
    {
        struct T_DL_Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->first = NULL;
    list->end = NULL;
    list->size = 0;
    return T_DL_LIST_SUCCUESS;
}
int t_DL_list_destroy(T_DL_List *list)
{
    return t_DL_list_clear(list);
}

struct T_DL_Node *_t_DL_list_nodeInit(size_t typeSize)
{
    struct T_DL_Node *newNode = malloc(sizeof(struct T_DL_Node));
    if (newNode == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for node.\n"
               "\x1B[0m");
        return NULL;
    }

    newNode->data = malloc(typeSize);
    if (newNode->data == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for data.\n"
               "\x1B[0m");
        free(newNode);
        return NULL;
    }
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

struct T_DL_Node *_t_DL_list_nodeBegin(T_DL_List *list)
{
    assert(list != NULL);
    if (list == NULL)
    {
        return NULL;
    }
    return list->first;
}
struct T_DL_Node *_t_DL_list_nodeEnd(T_DL_List *list)
{
    assert(list != NULL);
    if (list == NULL)
    {
        return NULL;
    }
    return list->end;
}
struct T_DL_Node *_t_DL_list_nodeAt(T_DL_List *list, size_t index)
{
    assert(list != NULL);
    if (list == NULL)
    {
        return NULL;
    }
    if (index >= list->size)
    {
        printf("\x1B[31m"
               "Index out of bounds. size: %d\n"
               "\x1B[0m",
               list->size);
        return NULL;
    }
    struct T_DL_Node *current = list->first;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current;
}