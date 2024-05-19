#ifndef TIN_PAIR
#define TIN_PAIR
#include "stddef.h"
#include "../utilities/func.h"

typedef struct T_Pair
{
    void *first;
    void *second;

} T_Pair;

T_Pair T_pair_init();
T_Pair T_pair_init_with(const void *first, size_t first_typeSize, const void *second, size_t second_typeSize);
void T_pair_destroy(T_Pair *pair);

void *T_pair_getFirst(const T_Pair *pair);
void *T_pair_getSecond(const T_Pair *pair);

int T_pair_setFirst(T_Pair *pair, const void *element, size_t first_typeSize);
int T_pair_setSecond(T_Pair *pair, const void *element, size_t second_typeSize);

// Display
void t_pair_display(const T_Pair *pair, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);

#define T_PAIR_NEW() T_pair_init()
#define T_PAIR_NEW_WITH(first, first_type, second, second_type) T_pair_init_with(first ,sizeof(first_type) ,second ,sizeof(second_type))
#define T_PAIR_FIRST_AS(type, pair) *(type *)T_pair_getFirst(pair)
#define T_PARI_SECOND_AS(type, pair) *(type *)T_pair_getSecond(pair)
#endif