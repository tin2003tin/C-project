#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define T_QUEUE_DEFAULT_SIZE 0
#define T_QUEUE_DEFAULT_CAPACITY 1

#define T_QUEUE_GROW_COND 100
#define T_QUEUE_GROW_RATE 200

#define T_QUEUE_SHRINK_COND 25
#define T_QUEUE_SHRINK_RATE 50

#define T_QUEUE_ERROR 1
#define T_QUEUE_SUCCUESS 0

struct T_Queue
{
    void *data;
    size_t typeSize;

    void *first;
    void *roar;

    size_t capacity;
    size_t size;

    size_t growCond;
    size_t growRate;

    size_t shrinkCond;
    size_t shrinkRate;
};

T_Queue *t_queue_init(size_t typeSize)
{
    return t_queue_custom_init(typeSize, T_QUEUE_DEFAULT_CAPACITY, T_QUEUE_GROW_COND, T_QUEUE_GROW_RATE, T_QUEUE_SHRINK_COND, T_QUEUE_SHRINK_RATE);
}

T_Queue *t_queue_custom_init(size_t typeSize, size_t capacity, size_t growCond, size_t growRate, size_t shrinkCond, size_t shrinkRate)
{
    if (capacity == 0)
    {
        printf("\x1B[31m"
               "Capacity must be greater than 0.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (growCond > 100)
    {
        printf("\x1B[31m"
               "GrowCond must be lower than 100\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (growRate < 100)
    {
        printf("\x1B[31m"
               "GrowRate must be greater than 100\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (shrinkCond > 100)
    {
        printf("\x1B[31m"
               "ShrinkCond must be lower than 100\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (shrinkRate > 100)
    {
        printf("\x1B[31m"
               "ShrinkRate must be lower than 100\n"
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
    queue->growCond = growCond;
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

int t_queue_enqueue(T_Queue *queue, void *element)
{
    assert(queue != NULL);
    if (queue == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_QUEUE_ERROR;
    }
}

int _t_queue_growable(const T_Queue *queue)
{
    if (queue->size > queue->capacity * (queue->growCond) / 100)
    {
        return 0;
    }
    return 1;
}

int _t_queue_expand(T_Queue *queue)
{
    assert(queue != NULL);
    if (queue == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_QUEUE_ERROR;
    }
    void *new_location = realloc(queue->data, queue->capacity * T_QUEUE_DEFAULT_CAPACITY);
}
