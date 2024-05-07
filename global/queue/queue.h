#ifndef TIN_QUEUE_H
#define TIN_QUEUE_H

#include <stddef.h>

typedef struct T_Queue
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
} T_Queue;

// Contructor
T_Queue t_queue_init(size_t typeSize);
T_Queue t_queue_custom_init(size_t typeSize, size_t capacity, size_t growCond, size_t growRate, size_t shrinkCond, size_t shrinkRate);
// Destructor
void t_queue_destroy(T_Queue *queue);

// Getter
size_t t_queue_get_capacity(const T_Queue *queue);
size_t t_queue_get_size(const T_Queue *queue);
size_t t_queue_get_typeSize(const T_Queue *queue);
size_t t_queue_get_growRate(const T_Queue *queue);
size_t t_queue_get_shrinkCond(const T_Queue *queue);
size_t t_queue_get_shrinkRate(const T_Queue *queue);

// Insert,Remove
int t_queue_enqueue(T_Queue *queue, void *element);

// utilities
#define T_QUEUE_NEW(type) t_queue_init(sizeof(type))
#define T_QUEUE_SIZE(queue) t_queue_get_size(queue)
#endif
