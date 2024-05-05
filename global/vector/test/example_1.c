#include <stdio.h>
#include <stdlib.h>

#include "../vector.h"

// gcc .\global\vector\test\example.c global/vector/vector.c -o out/vector_example_1
int main(int argc, const char *argv[])
{
    T_Vector vector = t_vector_init(sizeof(int));
    int x = 12;

    t_vector_push_back(&vector, &x);

    printf("vector_capacity: %zu\n", vector.capacity);
    printf("vector_size: %zu\n", vector.size);

    printf("1: %d\n", *((int *)vector.data));

    x = 123;

    t_vector_push_back(&vector, &x);
    printf("vector_capacity: %zu\n", vector.capacity);
    printf("vector_size: %zu\n", vector.size);

    x = 999;
    t_vector_push_back(&vector, &x);
    printf("vector_capacity: %zu\n", vector.capacity);
    printf("vector_size: %zu\n", vector.size);

    T_VECTOR_FOR_EACH(iter, vector)
    {
        printf(": %d\n", T_VECTOR_ITERATOR_VALUE_AS(int, iter));
    }
    printf("vector_size: %zu\n", vector.size);
    printf("vector_capacity: %zu\n", vector.capacity);
    x = 101;
    printf("after\n");
    t_vector_push_front(&vector, &x);
    x = 555;
    int err = t_vector_insert(&vector, &x, 3);
    if (err == T_VECTOR_ERROR)
    {
        printf("error naja\n");
        return 0;
    }

    T_VECTOR_FOR_EACH(iter, vector)
    {
        printf(": %d\n", T_VECTOR_ITERATOR_VALUE_AS(int, iter));
    }
    printf("vector_size: %zu\n", vector.size);
    printf("vector_capacity: %zu\n", vector.capacity);

    T_Iterator iter = t_vector_begin(&vector);
    printf("Test: %d\n", *T_VECTOR_ITERATOR_AS(int, iter));
    // t_vector_pop_front(&vector);
    // t_vector_erase(&vector,4);
    // t_vector_resize(&vector, 0);
    t_vector_clear(&vector);
    t_vector_push_back(&vector, &x);

    printf("deleted\n");
    T_VECTOR_FOR_EACH(iter, vector)
    {
        printf(": %d\n", T_VECTOR_ITERATOR_VALUE_AS(int, iter));
    }
    printf("vector_size: %zu\n", vector.size);
    printf("vector_capacity: %zu\n", vector.capacity);
    t_vector_destroy(&vector);
    return 0;
}
