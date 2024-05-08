#ifndef TIN_PRIORITY_QUEUE
#define TIN_PRIORITY_QUEUE
#include <stddef.h>
#include "../utilities/func.h"
#include "../queue/queue.h"

typedef struct T_PQueue
{
    T_CompareFunc compareFunc;
    T_Queue queue;
} T_PQueue;

// Contructor && Destructor
T_PQueue t_Pqueue_init(size_t typeSize, T_CompareFunc compareFunc);
T_PQueue t_Pqueue_clone(const T_PQueue *pqueue);
void t_Pqueue_destroy(T_PQueue *pqueue);

//  Get Pqueue Details
size_t t_Pqueue_get_size(const T_PQueue *pqueue);
size_t t_Pqueue_get_height(const T_PQueue *pqueue);
size_t t_Pqueue_get_capacity(const T_PQueue *pqueue);
size_t t_Pqueue_get_typeSize(const T_PQueue *pqueue);
bool t_Pqueue_isEmpty(const T_PQueue *pqueue);

// Getter
void *t_Pqueue_front(const T_PQueue *pqueue);

// Insert && Remove
int t_Pqueue_enqueue(T_PQueue *pqueue, void *element);
int t_Pqueue_dequeue(T_PQueue *pqueue);

// Display
void t_Pqueue_display(const T_PQueue *pqueue, T_DisplayFunc displayFunc);

// Private
void _t_Pqueue_fixUp(T_PQueue *pqueue);
void _t_Pqueue_fixDown(T_PQueue *pqueue);

#define T_PQUEUE_NEW(type, compareFunc) t_Pqueue_init(sizeof(type), compareFunc)
#define T_PQUEUE_NEW_INT() t_Pqueue_init(sizeof(int), t_utilities_compareInt)

#endif