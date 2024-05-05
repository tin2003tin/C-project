#include <stdio.h>

#include "./global/queue/queue.h"

int main()
{
    T_Queue *queue = T_QUEUE_NEW(int);
    if (queue == NULL)
    {
        printf("%d", queue);
    }
    printf("%d", T_QUEUE_SIZE(queue));
    return 0;
}