#include "../map.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    T_OrderMap map = t_ordermap_init(sizeof(char *), sizeof(int), t_utilities_compareString, t_utilities_equalString);
    char *id = "001";
    char *name = "tin";

    t_ordermap_insert(&map, id, name);

    printf("size: %d\n", map.size);
   
    char *foundName = t_ordermap_find(&map, id);
    name = "Job";
    if (foundName != NULL)
    {
        printf("%s : %s", "001", foundName);
    }
    else
    {
        printf("test");
    }
}