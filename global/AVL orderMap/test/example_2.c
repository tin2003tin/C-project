#include <stdio.h>
#include "../map.h"
#include "../../utilities/func.h"

int main()
{
    T_AVL_OrderMap map = T_AVL_ORDERMAP_NEW_INT_INT();
    for (int i = 1; i < 101; i++)
    {
        int price = 20 * i;
        t_AVL_ordermap_insert(&map, &i, &price);
    }
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int);
    printf("\nheight: %d\n\n", t_AVL_ordermap_get_height(&map));
    t_AVL_ordermap_display(&map, t_utilities_display_int);
    return 0;
}