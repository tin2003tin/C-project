#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

T_CSL_List t_CSL_list_init(int typeSize)
{
    T_CSL_List list;
    list.first = NULL;
    list.end = NULL;
    list.typeSize = typeSize;
    list.size = 0;
    return list;
}
T_CSL_List t_CSL_list_clone(const T_CSL_List *list)
{
    T_CSL_List clone_list;
    clone_list = t_CSL_list_init(list->typeSize);

    struct T_CSL_Node *current = list->first;
    if (current != NULL)
    {
        do
        {
            t_CSL_list_insertAtEnd(&clone_list, current->data);
            current = current->next;
        } while (current != list->first);
    }

    clone_list.size = list->size;
    return clone_list;
}

int t_CSL_list_insertAtEnd(T_CSL_List *list, void *element)
{
    assert(list != NULL);
    if (list == NULL)
    {
        printf("\x1B[31m"
               "list is null\n"
               "\x1B[0m");
        return T_CSL_LIST_ERROR;
    }

    struct T_CSL_Node *newNode = _t_CSL_list_nodeInit(list->typeSize);
    if (newNode == NULL)
    {
        return T_CSL_LIST_ERROR;
    }
    memcpy(newNode->data, element, list->typeSize);

    if (list->first == NULL)
    {
        list->first = newNode;
        newNode->next = newNode;
    }
    else
    {
        list->end->next = newNode;
        newNode->next = list->first;
    }

    list->end = newNode;
    list->size++;
    return T_CSL_LIST_SUCCESS;
}

int t_CSL_list_insertAtBegin(T_CSL_List *list, void *element)
{
    if (list == NULL)
    {
        printf("\x1B[31m"
               "list is null\n"
               "\x1B[0m");
        return T_CSL_LIST_ERROR;
    }

    struct T_CSL_Node *newNode = _t_CSL_list_nodeInit(list->typeSize);
    if (newNode == NULL)
    {
        return T_CSL_LIST_ERROR;
    }
    memcpy(newNode->data, element, list->typeSize);

    if (list->first == NULL)
    {
        list->first = newNode;
        list->end = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = list->first;
        list->first = newNode;
        list->end->next = newNode;
    }
    list->size++;
    return T_CSL_LIST_SUCCESS;
}

int t_CSL_list_insertAt(T_CSL_List *list, void *element, size_t index)
{
    assert(list != NULL);
    index = index % (list->size + 1);
    if (index == 0)
    {
        return t_CSL_list_insertAtBegin(list, element);
    }

    if (index == list->size)
    {
        return t_CSL_list_insertAtEnd(list, element);
    }

    struct T_CSL_Node *newNode = _t_CSL_list_nodeInit(list->typeSize);
    if (newNode == NULL)
    {
        return T_CSL_LIST_ERROR;
    }
    memcpy(newNode->data, element, list->typeSize);

    struct T_CSL_Node *target = _t_CSL_list_nodeAt(list, index - 1);
    struct T_CSL_Node *next = target->next;

    target->next = newNode;
    newNode->next = next;
    list->size++;

    return T_CSL_LIST_SUCCESS;
}

int t_CSL_list_deleteAtEnd(T_CSL_List *list)
{
    assert(list != NULL);

    if (list->end == NULL)
    {
        printf("\x1B[31m"
               "list->end is null\n"
               "\x1B[0m");
        return T_CSL_LIST_ERROR;
    }

    if (list->first == list->end)
    {
        free(list->first->data);
        free(list->first);
        list->first = NULL;
        list->end = NULL;
    }
    else
    {
        struct T_CSL_Node *current = list->first;
        while (current->next != list->end)
        {
            current = current->next;
        }
        free(list->end->data);
        free(list->end);
        current->next = list->first;
        list->end = current;
    }
    list->size--;
    return T_CSL_LIST_SUCCESS;
}

int t_CSL_list_deleteAtBegin(T_CSL_List *list)
{
    assert(list != NULL);

    if (list->first == NULL)
    {
        printf("\x1B[31m"
               "list->first is null\n"
               "\x1B[0m");
        return T_CSL_LIST_ERROR;
    }
    if (list->first == list->end)
    {
        free(list->first->data);
        free(list->first);
        list->first = NULL;
        list->end = NULL;
    }
    else
    {
        struct T_CSL_Node *current = list->first;
        list->first = list->first->next;
        free(current->data);
        free(current);
        list->end->next = list->first;
    }
    list->size--;
    return T_CSL_LIST_SUCCESS;
}

int t_CSL_list_deleteAt(T_CSL_List *list, size_t index)
{
    assert(list != NULL);

    if (list->first == NULL)
    {
        printf("\x1B[31m"
               "list->first is null\n"
               "\x1B[0m");
        return T_CSL_LIST_ERROR;
    }
    if (index >= list->size)
    {
        printf("\x1B[31m"
               "Index out of bounds. size: %zu\n"
               "\x1B[0m",
               list->size);
        return T_CSL_LIST_ERROR;
    }
    if (index == 0)
    {
        return t_CSL_list_deleteAtBegin(list);
    }
    if (index == list->size - 1)
    {
        return t_CSL_list_deleteAtEnd(list);
    }
    struct T_CSL_Node *target = _t_CSL_list_nodeAt(list, index - 1);
    struct T_CSL_Node *next = target->next->next;
    free(target->next->data);
    free(target->next);
    target->next = next;
    list->size--;
    return T_CSL_LIST_SUCCESS;
}

void *t_CSL_list_getBegin(const T_CSL_List *list)
{
    struct T_CSL_Node *target = _t_CSL_list_nodeBegin(list);
    if (target->data == NULL)
    {
        return NULL;
    }
    return target->data;
}
void *t_CSL_list_getEnd(const T_CSL_List *list)
{
    struct T_CSL_Node *target = _t_CSL_list_nodeEnd(list);
    if (target->data == NULL)
    {
        return NULL;
    }
    return target->data;
}
void *t_CSL_list_getAt(const T_CSL_List *list, size_t index)
{
    struct T_CSL_Node *target = _t_CSL_list_nodeAt(list, index);
    if (target->data == NULL)
    {
        return NULL;
    }
    return target->data;
}

int t_CSL_list_clear(T_CSL_List *list)
{
    assert(list != NULL);

    if (list->first == NULL)
    {
        printf("\x1B[31m"
               "list->first is null\n"
               "\x1B[0m");
        return T_CSL_LIST_ERROR;
    }
    struct T_CSL_Node *current = list->first;
    do
    {
        struct T_CSL_Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    } while (current != list->first);
    list->first = NULL;
    list->end = NULL;
    list->size = 0;
    return T_CSL_LIST_SUCCESS;
}

int t_CSL_list_destroy(T_CSL_List *list)
{
    return t_CSL_list_clear(list);
}

struct T_CSL_Node *_t_CSL_list_nodeInit(size_t typeSize)
{
    struct T_CSL_Node *newNode = malloc(sizeof(struct T_CSL_Node));
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
    return newNode;
}

struct T_CSL_Node *_t_CSL_list_nodeBegin(const T_CSL_List *list)
{
    assert(list != NULL);
    if (list == NULL)
    {
        return NULL;
    }
    if (list->size == 0)
    {
        printf("\x1B[31m"
               "List is empty.\n"
               "\x1B[0m");
        return NULL;
    }
    return list->first;
}

struct T_CSL_Node *_t_CSL_list_nodeEnd(const T_CSL_List *list)
{
    assert(list != NULL);
    if (list == NULL)
    {
        return NULL;
    }
    if (list->size == 0)
    {
        printf("\x1B[31m"
               "List is empty.\n"
               "\x1B[0m");
        return NULL;
    }
    return list->end;
}

struct T_CSL_Node *_t_CSL_list_nodeAt(const T_CSL_List *list, size_t index)
{
    assert(list != NULL);
    if (list == NULL)
    {
        return NULL;
    }
    if (list->size == 0)
    {
        printf("\x1B[31m"
               "List is empty.\n"
               "\x1B[0m");
        return NULL;
    }
    index = index % list->size;
    struct T_CSL_Node *current = list->first;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current;
}
