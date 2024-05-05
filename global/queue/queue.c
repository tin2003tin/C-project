#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define T_QUEUE_DEFAULT_SIZE 0
#define T_QUEUE_DEFAULT_CAPACITY 1
#define T_QUEUE_GROW_RATE 2
#define T_QUEUE_SHRINK_COND 4
#define T_QUEUE_SHRINK_RATE 2

struct T_Queue
{
    void *data;
    size_t capacity;
    size_t size;
    size_t typeSize;
    size_t growRate;
    size_t shrinkCond;
    size_t shrinkRate;
};

T_Queue *t_queue_init(size_t typeSize)
{
    return t_queue_custom_init(typeSize, T_QUEUE_DEFAULT_CAPACITY, T_QUEUE_GROW_RATE, T_QUEUE_SHRINK_COND, T_QUEUE_SHRINK_RATE);
}

T_Queue *t_queue_custom_init(size_t typeSize, size_t capacity, size_t growRate, size_t shrinkCond, size_t shrinkRate)
{
    if (capacity == 0)
    {
        printf("\x1B[31m"
               "Capacity must be greater than 0.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }

    struct T_Queue *queue = malloc(sizeof(T_Queue));
    if (queue == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for queue.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }

    queue->data = malloc(capacity * typeSize);
    if (queue->data == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for queue data.\n"
               "\x1B[0m");
        free(queue);
        exit(EXIT_FAILURE);
    }

    queue->typeSize = typeSize;
    queue->capacity = capacity;
    queue->size = 0;
    queue->growRate = growRate;
    queue->shrinkCond = shrinkCond;
    queue->shrinkRate = shrinkRate;

    return queue;
}

void t_queue_destroy(T_Queue *queue)
{
    if (queue != NULL)
    {
        free(queue->data);
        queue->data = NULL;
        free(queue);
    }
}

size_t t_queue_get_capacity(const T_Queue *queue)
{
    return queue->capacity;
}

size_t t_queue_get_size(const T_Queue *queue)
{
    return queue->size;
}

size_t t_queue_get_typeSize(const T_Queue *queue)
{
    return queue->typeSize;
}

size_t t_queue_get_growRate(const T_Queue *queue)
{
    return queue->growRate;
}

size_t t_queue_get_shrinkCond(const T_Queue *queue)
{
    return queue->shrinkCond;
}

size_t t_queue_get_shrinkRate(const T_Queue *queue)
{
    return queue->shrinkRate;
}
