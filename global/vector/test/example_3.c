#include <stdio.h>
#include <stdbool.h>

#include "../vector.h"

int add(T_Vector *vector1, T_Vector *vector2, int number)
{
    T_Vector clone = t_vector_clone(vector2);
    for (int index = 0; index < number; index++)
    {
        t_vector_push_back(&clone, &index);
    }
    t_vector_push_back(vector1, &clone);
}

int main()
{
    T_Vector main_vector = t_vector_init(sizeof(T_Vector));
    T_Vector vector1 = t_vector_init(sizeof(int));
    T_Vector vector2 = t_vector_init(sizeof(int));
    T_Vector vector3 = t_vector_init(sizeof(int));
    T_Vector vector4 = t_vector_init(sizeof(int));

    for (int index = 0; index < 5; index++)
    {
        t_vector_push_back(&vector1, &index);
    }
    T_Vector clone = t_vector_clone(&vector1);
    t_vector_push_back(&main_vector, &clone);
    add(&main_vector, &vector2, 10);
    add(&main_vector, &vector3, 30);
    add(&main_vector, &vector4, 40);
    t_vector_destroy(&vector1);
    t_vector_destroy(&vector2);
    t_vector_destroy(&vector3);
    t_vector_destroy(&vector4);

    for (int i = 0; i < main_vector.size; i++)
    {
        T_Vector top = T_VECTOR_GET_VALUE_AS(T_Vector, &main_vector, i);
        printf("vector: %d\n", i);
        printf("size: %d\n", top.size);
        for (int index = 0; index < top.size; index++)
        {
            printf("%d ", T_VECTOR_GET_VALUE_AS(int, &top, index));
        }
        printf("\n");
    }

    return 0;
}