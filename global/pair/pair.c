#include "pair.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define T_PAIR_ERROR 1
#define T_PAIR_SUCCESS 0
T_Pair T_pair_init()
{
    T_Pair pair;
    pair.first = NULL;
    pair.second = NULL;
    return pair;
}
T_Pair T_pair_init_with(const void *first, size_t first_typeSize, const void *second, size_t second_typeSize)
{
    T_Pair pair = T_pair_init();
    if (T_pair_setFirst(&pair, first, first_typeSize) == T_PAIR_ERROR || T_pair_setSecond(&pair, second, second_typeSize) == T_PAIR_ERROR)
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

int T_pair_setFirst(T_Pair *pair, const void *element, size_t first_typeSize)
{
    assert(pair != NULL);

    void *new_first = malloc(first_typeSize);
    if (new_first == NULL)
    {
        return T_PAIR_ERROR;
    }

    memcpy(new_first, element, first_typeSize);

    if (pair->first != NULL)
    {
        free(pair->first);
    }

    pair->first = new_first;
    return T_PAIR_SUCCESS;
}

int T_pair_setSecond(T_Pair *pair, const void *element, size_t second_typeSize)
{
    assert(pair != NULL);
    void *new_second = malloc(second_typeSize);
    if (new_second == NULL)
    {
        return T_PAIR_ERROR;
    }
    memcpy(new_second, element, second_typeSize);

    if (pair->second != NULL)
    {
        free(pair->second);
    }
    pair->second = new_second;
    return T_PAIR_SUCCESS;
}

void t_pair_display(const T_Pair *pair, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    printf("{");
    displayFunc1(pair->first);
    printf(":");
    displayFunc2(pair->second);
    printf("}");
}