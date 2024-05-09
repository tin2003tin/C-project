#include <stdio.h>
#include "../pair.h"

T_Pair makePair()
{
    T_Pair pair3 = T_PAIR_NEW(int, int);
    int id = 999;
    int price = 999;
    pair3.first = &id;
    pair3.second = &price;
    return pair3;
}

int main()
{
    T_Pair pair1 = T_PAIR_NEW(int, int);
    int id = 1;
    int price = 100;
    T_pair_setFirst(&pair1, &id);
    T_pair_setSecond(&pair1, &price);
    id = 2;
    price = 200;
    T_Pair pair2 = T_pair_init_with(sizeof(int), sizeof(int), &id, &price);
    // T_pair_destroy(&pair1);
    if (pair1.first != NULL)
    {
        printf("(%d,%d)\n", T_PAIR_FIRST_AS(int, &pair1), T_PARI_SECOND_AS(int, &pair1));
    }
    printf("(%d,%d)\n", T_PAIR_FIRST_AS(int, &pair2), T_PARI_SECOND_AS(int, &pair2));
    id = 3;
    price = 350;
    T_Pair pair3 = makePair();
    printf("(%d,%d)\n", T_PAIR_FIRST_AS(int, &pair3), T_PARI_SECOND_AS(int, &pair3));
}
