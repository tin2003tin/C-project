#ifndef TIN_HASHMAP
#include "stddef.h"
#include "../vector/vector.h"

struct T_HashMap_Bucket 
{
    T_Vector vector;
};


typedef struct T_HashMap {
    size_t size;
    T_Vector table;

} T_HashMap;



#endif