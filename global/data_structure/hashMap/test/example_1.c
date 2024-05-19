#include <stdio.h>
#include "global/data_structure/hashMap/hashmap.h"
#include "global/data_structure/AVL_orderMap/AVL_orderMap.h"

int main()
{
    T_HashMap hashmap = t_hashmap_init(sizeof(int), sizeof(int), t_utilities_hash_int, t_utilities_equalInt);
    for (int i = 1; i < 100; i++)
    {
        int age = 5 * i;
        t_hashmap_put(&hashmap, &i, &age);
    }
    T_AVL_OrderMap map = T_AVL_ORDERMAP_NEW_INT_INT();
    printf("size: %ld\n", hashmap.size);
    printf("bucketLength: %ld\n", hashmap.bucketsLength);
    for (size_t i = 0; i < hashmap.bucketsLength; i++)
    {
        printf("bucket %ld\n", i + 1);
        for (size_t j = 0; j < hashmap.buckets[i].vector.size; j++)
        {
            T_Pair pair = T_VECTOR_GET_VALUE_AS(T_Pair, &hashmap.buckets[i].vector, j);
            t_pair_display(&pair, t_utilities_display_int, t_utilities_display_int);
            size_t size = hashmap.buckets[i].vector.size;
            void *found = t_AVL_ordermap_find(&map, &size);
            if (found == NULL)
            {
                int one = 1;
                t_AVL_ordermap_insert(&map, &size, &one);
            }
            else
            {
                int new = *(int *)found + 1;
                t_AVL_ordermap_edit(&map, &size, &new);
            }
        }
        printf("\n");
    }
    t_AVL_ordermap_display(&map, t_utilities_display_int, t_utilities_display_int);

    // int key = 1;
    // t_hasmap_remove(&hashmap, &key);
    // printf("size: %d\n", hashmap.size);
    // int *number = t_hashmap_find(&hashmap, &key);
    // if (number == NULL)
    // {
    //     printf("The key is not found");
    // }
    // printf("{%d, %d}", key, *(int *)number);

    // int newId = 100;
    // int newAge = 50;
    // t_hashmap_put(&hashmap, &newId, &newAge);

    int newplusId = 50;
    int newplusAge = 50;
    int *foundPlus = t_hashmap_find(&hashmap, &newplusId);
    if (foundPlus == NULL)
    {
        printf("%d is not found\n", newplusId);
        return 0;
    }
    printf("Before {%d, %d}\n", newplusId, *foundPlus);
    t_hashmap_edit(&hashmap, &newplusId, &newplusAge);
    foundPlus = t_hashmap_find(&hashmap, &newplusId);
    if (foundPlus != NULL)
    {
        printf("After {%d, %d}\n", newplusId, *foundPlus);
    }

    t_hashmap_destroy(&hashmap);
    return 0;
}