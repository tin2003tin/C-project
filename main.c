#include <stdio.h>
#include <stdbool.h>

#include "global/vector/vector.h"
#include "global/hashMap/hashmap.h"
#include "global/pair/pair.h"
#include "global/utilities/hash.h"

int add(T_Vector *vector1, T_Vector *vector2, int number)
{
    T_Vector clone = t_vector_clone(vector2);
    for (int index = 0; index < number; index++)
    {
        T_Pair pair = T_PAIR_NEW_WITH(&index, int, &index, int);
        t_vector_push_back(&clone, &pair);
    }
    t_vector_push_back(vector1, &clone);
}

int main()
{
    T_HashMap hashmap = t_hashmap_init(sizeof(int));
    T_Vector vector1 = t_vector_init(sizeof(T_Pair));
    T_Vector vector2 = t_vector_init(sizeof(T_Pair));
    T_Vector vector3 = t_vector_init(sizeof(T_Pair));
    T_Vector vector4 = t_vector_init(sizeof(T_Pair));

    T_Vector clone = t_vector_clone(&vector1);
    t_vector_push_back(&hashmap.table, &clone);
    add(&hashmap.table, &vector2, 10);
    add(&hashmap.table, &vector3, 30);
    add(&hashmap.table, &vector4, 40);
    t_vector_destroy(&vector1);
    t_vector_destroy(&vector2);
    t_vector_destroy(&vector3);
    t_vector_destroy(&vector4);

    for (int i = 0; i < hashmap.table.size; i++)
    {
        T_Vector top = T_VECTOR_GET_VALUE_AS(T_Vector, &hashmap.table, i);
        printf("vector: %d\n", i);
        printf("size: %d\n", top.size);
        for (int index = 0; index < top.size; index++)
        {
            T_Pair pair = T_VECTOR_GET_VALUE_AS(T_Pair, &top, index);
            t_pair_display(&pair, t_utilities_display_int, t_utilities_display_int);
        }
        printf("\n");

    }

    return 0;
}