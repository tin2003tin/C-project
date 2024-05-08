#include "Pqueue.h"
#include "stdlib.h"
#include "assert.h"
#include <math.h>
#include "string.h"
#include <stdio.h>

#define T_PQUEUE_ERROR 1
#define T_PQUEUE_SUCCESS 0

T_PQueue t_Pqueue_init(size_t typeSize, T_CompareFunc compareFunc)
{
    assert(compareFunc != NULL);

    T_PQueue pqueue;
    pqueue.queue = t_queue_init(typeSize);
    pqueue.compareFunc = compareFunc;
    return pqueue;
}
T_PQueue t_Pqueue_clone(const T_PQueue *pqueue)
{
    assert(pqueue != NULL);

    T_PQueue clone_pqueue;
    clone_pqueue.compareFunc = pqueue->compareFunc;
    clone_pqueue.queue = t_queue_clone(&pqueue->queue);
    return clone_pqueue;
}
void t_Pqueue_destroy(T_PQueue *pqueue)
{
    assert(pqueue != NULL);

    t_vector_destroy(&(pqueue->queue));
}
size_t t_Pqueue_get_size(const T_PQueue *pqueue)
{
    assert(pqueue != NULL);
    assert(pqueue->queue.data != NULL);
    return pqueue->queue.size;
}
size_t t_Pqueue_get_height(const T_PQueue *pqueue)
{
    assert(pqueue != NULL);
    assert(pqueue->queue.data != NULL);
    if (pqueue->queue.size == 0)
    {
        return 0;
    }
    size_t height = (size_t)(log2(pqueue->queue.size) + 1);
    return height;
}
size_t t_Pqueue_get_capacity(const T_PQueue *pqueue)
{
    assert(pqueue != NULL);
    assert(pqueue->queue.data != NULL);
    assert(pqueue->queue.capacity != 0);
    return pqueue->queue.capacity;
}
size_t t_Pqueue_get_typeSize(const T_PQueue *pqueue)
{
    assert(pqueue != NULL);
    assert(pqueue->queue.data != NULL);
    assert(pqueue->queue.typeSize != 0);
    return pqueue->queue.typeSize;
}
bool t_Pqueue_isEmpty(const T_PQueue *pqueue)
{
    assert(pqueue != NULL);
    assert(pqueue->queue.data != NULL);
    return t_queue_isEmpty(&pqueue->queue);
}
void *t_Pqueue_front(const T_PQueue *pqueue)
{
    assert(pqueue != NULL);
    assert(pqueue->queue.data != NULL);
    if (t_Pqueue_isEmpty(pqueue))
    {
        printf("\x1B[31mPQueue is empty.\n\x1B[0m");
        return NULL;
    }
    return t_queue_front(&pqueue->queue);
}

int t_Pqueue_enqueue(T_PQueue *pqueue, void *element)
{
    assert(element != NULL);
    assert(pqueue != NULL);

    if (t_queue_enqueue(&(pqueue->queue), element) == 1)
    {
        return T_PQUEUE_ERROR;
    }
    _t_Pqueue_fixUp(pqueue);
}

int t_Pqueue_dequeue(T_PQueue *pqueue)
{
    assert(pqueue != NULL);
    if (t_Pqueue_isEmpty(pqueue))
    {
        printf("\x1B[31mPQueue is empty.\n\x1B[0m");
        return T_PQUEUE_ERROR;
    }
    memcpy(t_queue_front(&pqueue->queue), t_queue_roar(&pqueue->queue), pqueue->queue.typeSize);
    pqueue->queue.size--;
    if (_t_queue_should_shrink(&pqueue->queue))
    {
        if (_t_queue_shrink(&pqueue->queue))
        {
            return T_PQUEUE_ERROR;
        }
    }
    _t_Pqueue_fixDown(pqueue);
}

void _t_Pqueue_fixUp(T_PQueue *pqueue)
{
    size_t current_index = t_queue_get_size(&(pqueue->queue)) - 1;
    size_t parent_index;
    void *temp = malloc(pqueue->queue.typeSize);

    while (current_index != 0)
    {

        parent_index = (current_index - 1) / 2;
        void *current = pqueue->queue.data + current_index * pqueue->queue.typeSize;
        void *parent = pqueue->queue.data + parent_index * pqueue->queue.typeSize;

        if (pqueue->compareFunc(current, parent))
        {
            memcpy(temp, parent, pqueue->queue.typeSize);
            memcpy(parent, current, pqueue->queue.typeSize);
            memcpy(current, temp, pqueue->queue.typeSize);

            current_index = parent_index;
        }
        else
        {
            break;
        }
    }

    free(temp);
}

void _t_Pqueue_fixDown(T_PQueue *pqueue)
{
    size_t current_index = 0;
    size_t left_child_index;
    size_t right_child_index;
    void *temp = malloc(pqueue->queue.typeSize);

    while (true)
    {
        left_child_index = 2 * current_index + 1;
        right_child_index = 2 * current_index + 2;

        void *current = pqueue->queue.data + current_index * pqueue->queue.typeSize;
        void *left_child = pqueue->queue.data + left_child_index * pqueue->queue.typeSize;
        void *right_child = pqueue->queue.data + right_child_index * pqueue->queue.typeSize;

        size_t higher_child_index;
        if (right_child_index < t_queue_get_size(&(pqueue->queue)) &&
            pqueue->compareFunc(right_child, left_child))
        {
            higher_child_index = right_child_index;
        }
        else
        {
            higher_child_index = left_child_index;
        }

        void *higher_child = pqueue->queue.data + higher_child_index * pqueue->queue.typeSize;

        if (higher_child_index < t_queue_get_size(&(pqueue->queue)) &&
            pqueue->compareFunc(higher_child, current))
        {
            memcpy(temp, current, pqueue->queue.typeSize);
            memcpy(current, higher_child, pqueue->queue.typeSize);
            memcpy(higher_child, temp, pqueue->queue.typeSize);

            current_index = higher_child_index;
        }
        else
        {
            break;
        }
    }

    free(temp);
}

void t_Pqueue_display(const T_PQueue *pqueue, T_DisplayFunc displayFunc)
{
    for (size_t i = 0; i < pqueue->queue.size; i++)
    {
        displayFunc(pqueue->queue.first + i * pqueue->queue.typeSize);
    }
}