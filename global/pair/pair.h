#ifndef TIN_PAIR
#define TIN_PAIR
#include "stddef.h"
#include "../utilities/func.h"

typedef struct T_Pair
{
    void *first;
    void *second;
    size_t first_typeSize;
    size_t second_typeSize;
} T_Pair;

T_Pair T_pair_init(size_t first_typeSize, size_t second_typeSize);
T_Pair T_pair_init_with(size_t first_typeSize, size_t second_typeSize, const void *first, const void *second);
void T_pair_destroy(T_Pair *pair);

void *T_pair_getFirst(const T_Pair *pair);
void *T_pair_getSecond(const T_Pair *pair);

int T_pair_setFirst(T_Pair *pair, const void *element);
int T_pair_setSecond(T_Pair *pair, const void *element);

// Display
const void t_pair_display(const T_Pair *pair, T_DisplayFunc displayFunc);

#define T_PAIR_NEW(first_type, second_type) T_pair_init(sizeof(first_type), sizeof(second_type))
#define T_PAIR_NEW_WITH(first_type, second_type, first, second) T_pair_init_with(sizeof(first_type), sizeof(second_type), element1, element2)
#define T_PAIR_FIRST_AS(type, pair) *(type *)T_pair_getFirst(pair)
#define T_PARI_SECOND_AS(type, pair) *(type *)T_pair_getSecond(pair)
#endif