#include "pair.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define T_PAIR_ERROR 1
#define T_PAIR_SUCCESS 0
T_Pair T_pair_init(size_t first_typeSize, size_t second_typeSize)
{
    assert(first_typeSize > 0);
    assert(second_typeSize > 0);

    T_Pair pair;
    pair.first = NULL;
    pair.second = NULL;
    pair.first_typeSize = first_typeSize;
    pair.second_typeSize = second_typeSize;
    return pair;
}
T_Pair T_pair_init_with(size_t first_typeSize, size_t second_typeSize, const void *first, const void *second)
{
    T_Pair pair = T_pair_init(first_typeSize, second_typeSize);
    if (T_pair_setFirst(&pair, first) == T_PAIR_ERROR || T_pair_setSecond(&pair, second) == T_PAIR_ERROR)
    {
        T_pair_destroy(&pair);
        exit(EXIT_FAILURE);
    }
    return pair;
}
void T_pair_destroy(T_Pair *pair)
{
    assert(pair != NULL);
    free(pair->first);
    free(pair->second);
    pair->first = NULL;
    pair->second = NULL;
    pair->first_typeSize = 0;
    pair->second_typeSize = 0;
}

void *T_pair_getFirst(const T_Pair *pair)
{
    assert(pair != NULL);
    return pair->first;
}
void *T_pair_getSecond(const T_Pair *pair)
{
    assert(pair != NULL);
    return pair->second;
}

int T_pair_setFirst(T_Pair *pair, const void *element)
{
    assert(pair != NULL);
    if (pair->first == NULL)
    {
    }
    void *new_first = malloc(pair->first_typeSize);
    if (new_first == NULL)
    {
        return T_PAIR_ERROR;
    }
    memcpy(new_first, element, pair->first_typeSize);
    free(pair->first);
    pair->first = new_first;
    return T_PAIR_SUCCESS;
}
int T_pair_setSecond(T_Pair *pair, const void *element)
{
    assert(pair != NULL);
    void *new_second = malloc(pair->second_typeSize);
    if (new_second == NULL)
    {
        return T_PAIR_ERROR;
    }
    memcpy(new_second, element, pair->second_typeSize);
    free(pair->second);
    pair->second = new_second;
    return T_PAIR_SUCCESS;
}

const void t_pair_display(const T_Pair *pair, T_DisplayFunc displayFunc)
{
    printf("{");
    displayFunc(pair->first);
    printf(":");
    displayFunc(pair->second);
    printf("}");
}