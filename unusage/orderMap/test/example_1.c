#include "../map.h"
#include <stdio.h>

int main()
{
    // T_OrderMap map = t_ordermap_init(sizeof(int), sizeof(int), t_utilities_compareInt, t_utilities_equalInt);
    T_OrderMap map = T_ORDERMAP_NEW_INT_INT();
    int id = 10;
    int price = 200;
    t_ordermap_insert(&map, &id, &price);
    id = 40;
    price = 500;
    t_ordermap_insert(&map, &id, &price);
    id = 2;
    price = 100;
    t_ordermap_insert(&map, &id, &price);
    id = 20;
    price = 400;
    t_ordermap_insert(&map, &id, &price);
    id = 9;
    price = 1000;
    t_ordermap_insert(&map, &id, &price);
    printf("size: %d\n", map.size);
    t_ordermap_display(&map, t_utilities_display_int);

    printf("\nTry to insert same Id = 20\n");
    id = 20;
    price = 300;
    t_ordermap_insert(&map, &id, &price);

    printf("\nTry to Edit Id = 1\n");
    id = 1;
    price = 299;
    t_ordermap_edit(&map, &id, &price);
    printf("\nTry to Edit Id = 20\n");
    printf("Before\n");
    id = 20;
    price = 299;
    int *found = t_ordermap_find(&map, &id);
    if (found != NULL)
    {
        printf("{%d: %d}\n", id, *found);
    }
    printf("After editing\n");
    t_ordermap_edit(&map, &id, &price);
    found = t_ordermap_find(&map, &id);
    if (found != NULL)
    {
        printf("{%d: %d}\n", id, *found);
    }
    t_ordermap_display(&map, t_utilities_display_int);
    printf("\nTry to find Max Id\n");
    T_Pair *max = t_ordermap_max(&map);
    if (max != NULL)
    {
        t_pair_display(max, t_utilities_display_int);
        printf("\n");
    }
    printf("\nTry to find Min Id\n");
    T_Pair *min = t_ordermap_min(&map);
    if (min != NULL)
    {
        t_pair_display(max, t_utilities_display_int);
        printf("\n");
    }

    printf("\nTry to delete Id = 11\n");
    int deleteId = 11;
    t_ordermap_erase(&map, &deleteId);
    printf("\nTry to delete Id = 10\n");
    deleteId = 10;
    t_ordermap_erase(&map, &deleteId);
    printf("deleted Id = 10\n");
    printf("size: %d\n", map.size);
    found = t_ordermap_find(&map, &deleteId);
    if (found != NULL)
    {
        printf("(%d,%d)\n", deleteId, *found);
    }
    else
    {
        printf("%d is not found\n", deleteId);
    }
    t_ordermap_display(&map, t_utilities_display_int);
}