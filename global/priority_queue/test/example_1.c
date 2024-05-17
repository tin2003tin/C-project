#include "../Pqueue.h"
#include "stdio.h"

int main()
{
    T_PQueue pqueue = T_PQUEUE_NEW_INT();
    for (int i = 0; i < 100; i += 5)
    {
        t_Pqueue_enqueue(&pqueue, &i);
    }
    printf("size: %d\n", t_Pqueue_get_size(&pqueue));
    printf("capacity: %d\n", t_Pqueue_get_capacity(&pqueue));
    t_Pqueue_display(&pqueue, t_utilities_display_int);
    printf("\n");
    printf("front: %d\n", *(int *)t_Pqueue_front(&pqueue));
    printf("\nAfter dequeue 15 times\n");
    for (int i = 0; i < 15; i++)
    {
        t_Pqueue_dequeue(&pqueue);
    }
    printf("size: %d\n", t_Pqueue_get_size(&pqueue));
    printf("capacity: %d\n", t_Pqueue_get_capacity(&pqueue));
    t_Pqueue_display(&pqueue, t_utilities_display_int);
    printf("\n");
    printf("front: %d\n", *(int *)t_Pqueue_front(&pqueue));

    return 0;
}