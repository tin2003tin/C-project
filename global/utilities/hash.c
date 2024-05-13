#include "hash.h"
#include <string.h>

unsigned long t_utilities_hash_int(const void *x)
{
    unsigned long y = *(unsigned long *)x;
    y = ((y >> 16) ^ y) * 0x45d9f3b;
    y = ((y >> 16) ^ y) * 0x45d9f3b;
    y = (y >> 16) ^ y;
    return y;
}

unsigned long t_utilities_hash_string(const void *str)
{
    unsigned long hash = 5381;
    const unsigned char *s = (const unsigned char *)str;
    int c;

    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

unsigned long t_utilities_hash_float(const void *x)
{
    unsigned int hash;
    memcpy(&hash, x, sizeof(unsigned int));
    return hash;
}