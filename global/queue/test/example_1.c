#include <stdio.h>
#include "../queue.h"

int main()
{
    T_Queue queue = T_QUEUE_NEW(int);
    int x = 10;

    for (int i = 0; i < 100; i++)
    {
        t_queue_enqueue(&queue, &i);
        if ((i) % 5 == 0)
        {
            t_queue_dequeue(&queue);
        }
    }
    printf("size: %d\n", queue.size);
    printf("cap: %d\n", queue.capacity);
    printf("data pointer: %p\n", queue.data);
    printf("first pointer: %p\n", queue.first);
    printf("roar pointer: %p\n", queue.roar);
    printf("front: %d\n", T_QUEUE_FRONT_AS(int, &queue));
    printf("roar: %d\n", T_QUEUE_ROAR_AS(int, &queue));

    for (int i = 0; i < 50; i++)
    {
        t_queue_dequeue(&queue);
    }
    printf("\nAfter shrinking size 80 -> 30\n");
    printf("size: %d\n", queue.size);
    printf("cap: %d\n", queue.capacity);
    printf("data pointer: %p\n", queue.data);
    printf("first pointer: %p\n", queue.first);
    printf("roar pointer: %p\n", queue.roar);
    printf("front: %d\n", T_QUEUE_FRONT_AS(int, &queue));
    printf("roar: %d\n", T_QUEUE_ROAR_AS(int, &queue));

    return 0;
}