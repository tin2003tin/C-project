#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define T_QUEUE_DEFAULT_SIZE 0
#define T_QUEUE_DEFAULT_CAPACITY 1

#define T_QUEUE_GROW_COND 100
#define T_QUEUE_GROW_RATE 200

#define T_QUEUE_SHRINK_COND 25
#define T_QUEUE_SHRINK_RATE 50

#define T_QUEUE_ERROR 1
#define T_QUEUE_SUCCESS 0

T_Queue t_queue_init(size_t typeSize)
{
    return t_queue_custom_init(typeSize, T_QUEUE_DEFAULT_CAPACITY, T_QUEUE_GROW_COND, T_QUEUE_GROW_RATE, T_QUEUE_SHRINK_COND, T_QUEUE_SHRINK_RATE);
}

T_Queue t_queue_custom_init(size_t typeSize, size_t capacity, size_t growCond, size_t growRate, size_t shrinkCond, size_t shrinkRate)
{
    if (capacity == 0 || growCond > 100 || growRate < 100 || shrinkCond > 100 || shrinkRate > 100)
    {
        fprintf(stderr, "Invalid parameters for queue initialization.\n");
        exit(EXIT_FAILURE);
    }

    void *data = malloc(capacity * typeSize);
    if (data == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for queue data.\n");
        exit(EXIT_FAILURE);
    }

    T_Queue queue;
    queue.data = data;
    queue.typeSize = typeSize;
    queue.capacity = capacity;
    queue.size = 0;
    queue.growCond = growCond;
    queue.growRate = growRate;
    queue.shrinkCond = shrinkCond;
    queue.shrinkRate = shrinkRate;
    queue.first = queue.data;

    return queue;
}

T_Queue t_queue_clone(const T_Queue *queue)
{
    assert(queue != NULL);

    T_Queue clone_queue;
    clone_queue.data = malloc(queue->capacity * queue->typeSize);
    if (clone_queue.data == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for queue data.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(clone_queue.data, queue->data, queue->capacity * queue->typeSize);
    clone_queue.capacity = queue->capacity;
    clone_queue.first = clone_queue.data;
    clone_queue.size = queue->size;
    clone_queue.typeSize = queue->typeSize;
    clone_queue.growCond = queue->growCond;
    clone_queue.growRate = queue->growRate;
    clone_queue.shrinkCond = queue->shrinkCond;
    clone_queue.shrinkRate = queue->shrinkRate;
    return clone_queue;
}

void t_queue_destroy(T_Queue *queue)
{
    if (queue != NULL)
    {
        free(queue->data);
        queue->data = NULL;
        queue->capacity = 0;
        queue->first = NULL;
        queue->growCond = 0;
        queue->growRate = 0;
        queue->shrinkCond = 0;
        queue->shrinkRate = 0;
        queue->typeSize = 0;
        queue->size = 0;
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

int t_queue_enqueue(T_Queue *queue, const void *element)
{
    assert(queue != NULL);
    assert(queue->data != NULL);
    assert(element != NULL);

    if (_t_queue_growable(queue))
    {
        if (_t_queue_expand(queue) == T_QUEUE_ERROR)
        {
            fprintf(stderr, "Failed to expand the queue.\n");
            return T_QUEUE_ERROR;
        }
    }

    memcpy((char *)queue->first + queue->size * queue->typeSize, element, queue->typeSize);
    queue->size++;

    return T_QUEUE_SUCCESS;
}

int t_queue_dequeue(T_Queue *queue)
{
    assert(queue != NULL);
    assert(queue->data != NULL);

    if (queue->size == 0)
    {
        fprintf(stderr, "Queue is empty. Cannot dequeue.\n");
        return T_QUEUE_ERROR;
    }

    queue->first = (char *)queue->first + queue->typeSize;
    queue->size--;

    if (_t_queue_should_shrink(queue))
    {
        if (_t_queue_shrink(queue) == T_QUEUE_ERROR)
        {
            return T_QUEUE_ERROR;
        }
    }

    return T_QUEUE_SUCCESS;
}

void *t_queue_front(const T_Queue *queue)
{
    assert(queue != NULL);
    assert(queue->data != NULL);
    if (t_queue_isEmpty(queue))
    {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }
    return queue->first;
}

void *t_queue_roar(const T_Queue *queue)
{
    assert(queue != NULL);
    assert(queue->data != NULL);
    if (t_queue_isEmpty(queue))
    {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }
    return (char *)queue->first + (queue->size - 1) * queue->typeSize;
}

bool t_queue_isEmpty(const T_Queue *queue)
{
    assert(queue != NULL);
    assert(queue->data != NULL);
    return queue->size == 0;
}

void t_queue_display(const T_Queue *queue, T_DisplayFunc displayFunc)
{
    for (size_t i = 0; i < queue->size; i++)
    {
        displayFunc((char *)queue->first + i * queue->typeSize);
    }
}

bool _t_queue_growable(const T_Queue *queue)
{
    if ((char *)queue->first + queue->size * queue->typeSize >= (char *)queue->data + (queue->capacity * (queue->growCond) / 100) * queue->typeSize)
    {
        return true;
    }
    return false;
}

int _t_queue_expand(T_Queue *queue)
{
    assert(queue != NULL);
    assert(queue->data != NULL);

    size_t newCapacity = queue->capacity + (queue->capacity * queue->growRate) / 100;
    if (newCapacity <= queue->capacity)
    {
        newCapacity = queue->capacity + 1;
    }

    size_t newSize = newCapacity * queue->typeSize;

    void *newLocation = malloc(newSize);
    if (newLocation == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for expand.\n");
        return T_QUEUE_ERROR;
    }

    size_t copySize = queue->size * queue->typeSize;
    memcpy(newLocation, queue->data, copySize);

    free(queue->data);

    queue->data = newLocation;
    queue->capacity = newCapacity;
    queue->first = newLocation;

    return T_QUEUE_SUCCESS;
}

bool _t_queue_should_shrink(const T_Queue *queue)
{
    assert(queue != NULL);
    assert(queue->data != NULL);
    assert(queue->capacity != 0);
    if (queue->size < (queue->capacity * queue->shrinkCond) / 100)
    {
        return true;
    }
    return false;
}

int _t_queue_shrink(T_Queue *queue)
{
    assert(queue != NULL);
    assert(queue->data != NULL);

    size_t newCapacity = (queue->capacity * queue->shrinkRate) / 100;
    if (newCapacity < T_QUEUE_DEFAULT_CAPACITY)
    {
        newCapacity = T_QUEUE_DEFAULT_CAPACITY;
    }

    void *newLocation = malloc(newCapacity * queue->typeSize);
    if (newLocation == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory for shrink.\n");
        return T_QUEUE_ERROR;
    }

    memcpy(newLocation, queue->first, (queue->size + 1) * queue->typeSize);
    free(queue->data);

    queue->data = newLocation;
    queue->capacity = newCapacity;
    queue->first = newLocation;

    return T_QUEUE_SUCCESS;
}