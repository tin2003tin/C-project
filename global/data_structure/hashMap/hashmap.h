#ifndef TIN_HASHMAP
#include <stddef.h>
#include "../pair/pair.h"
#include "../vector/vector.h"
#include "../utilities/hash.h"
#include "../utilities/func.h"

struct T_HashMap_Bucket
{
    T_Vector vector;
};

typedef struct T_HashMap
{
    size_t size;
    size_t key_typeSize;
    size_t value_typeSize;
    T_HashFunc hashFunc;
    T_EqualFunc equalFunc;
    struct T_HashMap_Bucket *buckets;
    size_t bucketsLength;
    size_t bucket_typeSize;
} T_HashMap;

// typedef struct T_HashMap_Iterator
// {
//     const T_HashMap *hashmap;
//     struct T_HashMap_Bucket *bucketPointer;
//     T_Iterator valuePointer;
// } T_HashMap_Iterator;

T_HashMap t_hashmap_init(size_t key_typeSize, size_t value_typeSize, T_HashFunc hashFunc, T_EqualFunc equalFunc);
int t_hashmap_put(T_HashMap *hashmap, void *key, void *value);
void t_hashmap_destroy(T_HashMap *hashmap);
int t_hashmap_assign(T_HashMap *hashmap, void *key, void *value);
void *t_hashmap_find(T_HashMap *hashmap, void *key);
int t_hashmap_edit(T_HashMap *hashmap, void *key, void *value);
int t_hasmap_remove(T_HashMap *hashmap, void *key);

// T_HashMap_Iterator t_hashmap_iter_begin(const T_HashMap *hashmap);
// T_HashMap_Iterator t_hashmap_iter_next(T_HashMap_Iterator *iterator);

#endif