#include <stdio.h>
#include "global/data_structure/queue/queue.h"

int main()
{
    T_Queue queue = T_QUEUE_NEW(int);

    for (int i = 0; i < 100; i++)
    {
        t_queue_enqueue(&queue, &i);
        // if ((i) % 5 == 0)
        // {
        //     t_queue_dequeue(&queue);
        // }
    }
    printf("size: %ld\n", queue.size);
    printf("cap: %ld\n", queue.capacity);
    printf("data pointer: %p\n", queue.data);
    printf("first pointer: %p\n", queue.first);
    printf("roar pointer: %p\n", t_queue_roar(&queue));
    printf("front: %d\n", T_QUEUE_FRONT_AS(int, &queue));
    printf("roar: %d\n", T_QUEUE_ROAR_AS(int, &queue));
    t_queue_display(&queue, t_utilities_display_int);
    for (int i = 0; i < 80; i++)
    {
        t_queue_dequeue(&queue);
    }

    printf("\nAfter shrinking size 100 -> 20\n");
    printf("size: %ld\n", queue.size);
    printf("cap: %ld\n", queue.capacity);
    printf("data pointer: %p\n", queue.data);
    printf("first pointer: %p\n", queue.first);
    printf("roar pointer: %p\n", t_queue_roar(&queue));
    printf("front: %d\n", T_QUEUE_FRONT_AS(int, &queue));
    printf("roar: %d\n", T_QUEUE_ROAR_AS(int, &queue));
    t_queue_display(&queue, t_utilities_display_int);
    t_queue_destroy(&queue);

    return 0;
}