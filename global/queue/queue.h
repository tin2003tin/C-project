#ifndef TIN_QUEUE_H
#define TIN_QUEUE_H

#include <stddef.h>
#include <stdbool.h>
#include "../utilities/func.h"

typedef struct T_Queue
{
    void *data;
    size_t typeSize;

    void *first;

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
T_Queue t_queue_clone(const T_Queue *queue);
// Destructor
void t_queue_destroy(T_Queue *queue);

// Getter
size_t t_queue_get_capacity(const T_Queue *queue);
size_t t_queue_get_size(const T_Queue *queue);
size_t t_queue_get_typeSize(const T_Queue *queue);
size_t t_queue_get_growRate(const T_Queue *queue);
size_t t_queue_get_shrinkCond(const T_Queue *queue);
size_t t_queue_get_shrinkRate(const T_Queue *queue);
bool t_queue_isEmpty(const T_Queue *queue);

// Insert,Remove
int t_queue_enqueue(T_Queue *queue, void *element);
int t_queue_dequeue(T_Queue *queue);

// Getter
void *t_queue_front(const T_Queue *queue);
void *t_queue_roar(const T_Queue *queue);

void t_queue_display(const T_Queue *pqueue, T_displayFunc displayFunc);

// Private
bool _t_queue_growable(const T_Queue *queue);
int _t_queue_expand(T_Queue *queue);
bool _t_queue_should_shrink(const T_Queue *queue);
int _t_queue_shrink(T_Queue *T_queue);

// utilities
#define T_QUEUE_NEW(type) t_queue_init(sizeof(type))
#define T_QUEUE_FRONT_AS(type, queue) *(type *)t_queue_front(queue)
#define T_QUEUE_ROAR_AS(type, queue) *(type *)t_queue_roar(queue)
#endif
