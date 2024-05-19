#include <stdio.h>
#include "global/data_structure/pair/pair.h"

int main()
{
    T_Pair pair1 = T_PAIR_NEW();
    int id = 1;
    int price = 100;
    T_pair_setFirst(&pair1, &id, sizeof(int));
    T_pair_setSecond(&pair1, &price, sizeof(int));
    id = 2;
    price = 200;
    T_Pair pair2 = T_pair_init_with(&id, sizeof(int), &price, sizeof(int));

    if (pair1.first != NULL)
    {
        printf("(%d,%d)\n", T_PAIR_FIRST_AS(int, &pair1), T_PARI_SECOND_AS(int, &pair1));
    }
    printf("(%d,%d)\n", T_PAIR_FIRST_AS(int, &pair2), T_PARI_SECOND_AS(int, &pair2));
    id = 3;
    price = 350;
    T_pair_destroy(&pair1);
    T_pair_destroy(&pair2);
}
