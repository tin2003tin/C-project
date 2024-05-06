#include <stdio.h>
#include <stdlib.h>

#include "../vector.h"

int main(int argc, const char *argv[])
{
    T_Vector *vector = t_vector_init(sizeof(int));
    printf("vector_capacity: %zu\n", t_vector_get_capacity(vector));
    printf("vector_size: %zu\n", t_vector_get_size(vector));
    int x = 12;
    t_vector_push_back(vector, &x);
    x = 10;
    t_vector_push_back(vector, &x);
    x = 999;
    t_vector_push_front(vector, &x);
    x = 1;
    t_vector_insert(vector, &x, t_vector_iter_begin(vector));
    x = 2;
    t_vector_insert(vector, &x, t_vector_iter_end(vector));

    T_VECTOR_FOR_EACH(iter, vector)
    {
        printf("%d ", T_VECTOR_ITERATOR_VALUE_AS(int, iter));
    }
    printf("\n");

    x = 555;
    t_vector_insert(vector, &x, t_vector_iter_at(vector, 2));

    printf("After insert at index 2\n");
    T_VECTOR_FOR_EACH(iter, vector)
    {
        printf("%d ", T_VECTOR_ITERATOR_VALUE_AS(int, iter));
    }
    printf("\n");

    printf("vector_capacity: %zu\n", t_vector_get_capacity(vector));
    printf("vector_size: %zu\n", t_vector_get_size(vector));

    t_vector_pop_back(vector);
    t_vector_pop_front(vector);
    t_vector_erase(vector, t_vector_iter_at(vector, 1));

    printf("After deleting\n");
    T_VECTOR_FOR_EACH(iter, vector)
    {
        printf("%d ", T_VECTOR_ITERATOR_VALUE_AS(int, iter));
    }
    printf("\n");

    printf("%d\n", T_VECTOR_GET_VALUE_AS(int, vector, 0));
    printf("%d\n", *(int *)T_VECTOR_ITERATOR_AS(int, t_vector_iter_begin(vector)));
    printf("%d\n", T_VECTOR_ITERATOR_VALUE_AS(int, t_vector_iter_begin(vector)));
    printf("After clear\n");
    t_vector_clear(vector);
    printf("vector_capacity: %zu\n", t_vector_get_capacity(vector));
    printf("vector_size: %zu\n", t_vector_get_size(vector));
    printf("Try to destroy vector\n");
    t_vector_destroy(&vector);
    if (vector == NULL)
    {
        printf("destroy completely");
    }
    return 0;
}
