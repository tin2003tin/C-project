#include <stdio.h>
#include "global/data_structure/AVL_orderMap/AVL_orderMap.h"
#include "global/data_structure/utilities/func.h"

int main()
{
    T_AVL_OrderMap map = T_AVL_ORDERMAP_NEW_INT_INT();
    int id = 5;
    int age = 55;
    t_AVL_ordermap_insert(&map, &id, &age);
    id = 10;
    age = 40;
    t_AVL_ordermap_insert(&map, &id, &age);
    id = 15;
    age = 40;
    t_AVL_ordermap_insert(&map, &id, &age);
    t_AVL_ordermap_display(&map, t_utilities_display_int, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));
    id = 3;
    age = 40;
    t_AVL_ordermap_insert(&map, &id, &age);
    id = 2;
    age = 40;
    t_AVL_ordermap_insert(&map, &id, &age);
    printf("\n");
    t_AVL_ordermap_display(&map, t_utilities_display_int, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    id = 6;
    age = 40;
    t_AVL_ordermap_insert(&map, &id, &age);
    printf("\n");
    t_AVL_ordermap_display(&map, t_utilities_display_int, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    id = 4;
    age = 10;
    t_AVL_ordermap_insert(&map, &id, &age);
    printf("\n");
    t_AVL_ordermap_display(&map, t_utilities_display_int, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    id = 8;
    age = 10;
    t_AVL_ordermap_insert(&map, &id, &age);

    id = 7;
    age = 10;
    t_AVL_ordermap_insert(&map, &id, &age);
    printf("\n");
    t_AVL_ordermap_display(&map, t_utilities_display_int, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    id = 9;
    age = 12;
    t_AVL_ordermap_insert(&map, &id, &age);
    printf("\n");
    t_AVL_ordermap_display(&map, t_utilities_display_int, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    printf("\n=======\n After erase id = 4 \n=======\n");
    int delete_id = 4;
    t_AVL_ordermap_erase(&map, &delete_id);
    printf("\n");
    // t_AVL_ordermap_display(&map, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    printf("\n=======\n After erase id = 2 \n=======\n");
    delete_id = 2;
    t_AVL_ordermap_erase(&map, &delete_id);
    printf("\n");
    // t_AVL_ordermap_display(&map, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    printf("\n=======\n After erase id = 9 and id =15 \n=======\n");
    delete_id = 9;
    t_AVL_ordermap_erase(&map, &delete_id);
    delete_id = 15;
    t_AVL_ordermap_erase(&map, &delete_id);
    printf("\n");
    // t_AVL_ordermap_display(&map, t_utilities_display_int);
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));

    printf("\n=======\n After insert id = 1 and id =2 \n=======\n");
    id = 1;
    age = 12;
    t_AVL_ordermap_insert(&map, &id, &age);

    id = 2;
    age = 12;
    t_AVL_ordermap_insert(&map, &id, &age);

    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, t_utilities_display_int);
    printf("height: %ld\n", t_AVL_ordermap_get_height(&map));
    t_AVL_ordermap_destroy(&map);
    return 0;
}