#include "hash.h"

unsigned int t_utilities_hash_int(unsigned int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

unsigned long t_utilities_hash_string(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

unsigned int t_utilities_hash_float(float x)
{
    unsigned int hash;
    memcpy(&hash, &x, sizeof(unsigned int));
    return hash;
}