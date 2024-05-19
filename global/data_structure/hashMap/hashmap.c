#include "hashmap.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define T_HASHMAP_ERROR 1
#define T_HASHMAP_SUCCESS 0
#define T_HASHMAP_BUCKETSLENGTH 1
#define T_HASHMAP_LOADFACTOR_COND 1
#define T_HASHMAP_GROW_RATE 200

int _t_hashmap_init_buckets(T_HashMap *hashmap);
double _t_HashMap_loadFactor(const T_HashMap *hashmap);
int _t_HashMap_expand(T_HashMap *hashmap);
int _t_hashMap_Rehashing(T_HashMap *source, T_HashMap *destination);
void _t_hashmap_destroy_withoutPair(T_HashMap *hashmap);
T_Pair *_t_hashmap_findPair(T_HashMap *hashmap, void *key);
// struct T_HashMap_Bucket *_t_hashMap_bucket_iter_end(const T_HashMap *hashmap);
// void _t_hashMap_bucket_next(T_HashMap_Iterator *iterator);
// struct T_HashMap_Bucket *_t_hashMap_bucket_iter_begin(const T_HashMap *hashmap);
// void _t_hashmap_iter_toNextData(T_HashMap_Iterator *iterator);

T_HashMap t_hashmap_init(size_t key_typeSize, size_t value_typeSize, T_HashFunc hashFunc, T_EqualFunc equalFunc)
{
    assert(hashFunc != NULL);
    assert(equalFunc != NULL);

    T_HashMap hashmap;
    hashmap.size = 0;
    hashmap.key_typeSize = key_typeSize;
    hashmap.value_typeSize = value_typeSize;
    hashmap.bucket_typeSize = sizeof(struct T_HashMap_Bucket);
    hashmap.bucketsLength = T_HASHMAP_BUCKETSLENGTH;
    hashmap.hashFunc = hashFunc;
    hashmap.equalFunc = equalFunc;
    hashmap.buckets = malloc(hashmap.bucket_typeSize * hashmap.bucketsLength);
    if (hashmap.buckets == NULL)
    {
        fprintf(stderr, "Error: Failed to reallocate memory for buckets.\n");
        exit(EXIT_FAILURE);
    }
    if (_t_hashmap_init_buckets(&hashmap) == T_HASHMAP_ERROR)
    {
        exit(EXIT_FAILURE);
    }
    return hashmap;
}

void t_hashmap_destroy(T_HashMap *hashmap)
{
    assert(hashmap != NULL);

    for (size_t i = 0; i < hashmap->bucketsLength; i++)
    {
        T_Vector *vector = &hashmap->buckets[i].vector;

        for (size_t j = 0; j < vector->size; j++)
        {
            T_Pair *pair = (T_Pair *)(t_vector_iter_at(vector, j).pointer);
            if (pair != NULL)
            {
                T_pair_destroy(pair);
            }
        }

        t_vector_destroy(vector);
    }

    free(hashmap->buckets);
    hashmap->buckets = NULL;
    hashmap->bucketsLength = 0;
}

int t_hashmap_put(T_HashMap *hashmap, void *key, void *value)
{
    assert(hashmap != NULL);
    assert(key != NULL);
    assert(value != NULL);

    if (_t_hashmap_findPair(hashmap, key) != NULL)
    {
        fprintf(stderr, "Error: The key is already in hashMap\n");

        return T_HASHMAP_ERROR;
    }

    if (_t_HashMap_loadFactor(hashmap) >= T_HASHMAP_LOADFACTOR_COND)
    {
        if (_t_HashMap_expand(hashmap) == T_HASHMAP_ERROR)
        {
            return T_HASHMAP_ERROR;
        }
    }
    unsigned long hashKey = hashmap->hashFunc(key);
    size_t hashIndex = hashKey % hashmap->bucketsLength;
    T_Vector *targetBucket = &(hashmap->buckets[hashIndex].vector);
    hashmap->size++;
    T_Pair key_value = T_pair_init_with(key, hashmap->key_typeSize, value, hashmap->value_typeSize);
    t_vector_push_back(targetBucket, &key_value);

    return T_HASHMAP_SUCCESS;
}

int t_hashmap_assign(T_HashMap *hashmap, void *key, void *value)
{
    assert(hashmap != NULL);
    assert(key != NULL);
    assert(value != NULL);
    if (_t_HashMap_loadFactor(hashmap) >= T_HASHMAP_LOADFACTOR_COND)
    {
        if (_t_HashMap_expand(hashmap) == T_HASHMAP_ERROR)
        {
            return T_HASHMAP_ERROR;
        }
    }
    unsigned long hashKey = hashmap->hashFunc(key);
    size_t hashIndex = hashKey % hashmap->bucketsLength;
    T_Vector *targetBucket = &(hashmap->buckets[hashIndex].vector);
    T_Pair key_value;
    key_value.first = key;
    key_value.second = value;
    t_vector_push_back(targetBucket, &key_value);
    hashmap->size++;

    return T_HASHMAP_SUCCESS;
}

void *t_hashmap_find(T_HashMap *hashmap, void *key)
{
    assert(hashmap != NULL);
    assert(key != NULL);

    T_Pair *pair = _t_hashmap_findPair(hashmap, key);
    if (pair == NULL)
    {
        return NULL;
    }
    return pair->second;
}

int t_hasmap_remove(T_HashMap *hashmap, void *key)
{
    assert(hashmap != NULL);
    assert(key != NULL);
    unsigned long hashKey = hashmap->hashFunc(key);
    size_t hashIndex = hashKey % hashmap->bucketsLength;
    T_Vector *targetBucket = &(hashmap->buckets[hashIndex].vector);
    for (size_t i = 0; i < targetBucket->size; i++)
    {
        T_pair_destroy((T_Pair *)t_vector_iter_at(targetBucket, i).pointer);
        t_vector_erase(targetBucket, t_vector_iter_at(targetBucket, i));
        hashmap->size--;
        return T_HASHMAP_SUCCESS;
    }
    return T_HASHMAP_ERROR;
}

int t_hashmap_edit(T_HashMap *hashmap, void *key, void *value)
{
    assert(hashmap != NULL);
    assert(key != NULL);
    assert(value != NULL);

    T_Pair *found = _t_hashmap_findPair(hashmap, key);
    if (found == NULL)
    {
        fprintf(stderr, "Error: The key does not be found in the hashMap\n");
        return T_HASHMAP_ERROR;
    }

    if (T_pair_setSecond(found, value, hashmap->value_typeSize) == 1)
    {
        return T_HASHMAP_ERROR;
    }
    return T_HASHMAP_SUCCESS;
}
int _t_hashmap_init_buckets(T_HashMap *hashmap)
{
    for (size_t i = 0; i < hashmap->bucketsLength; i++)
    {
        hashmap->buckets[i].vector = t_vector_init(sizeof(T_Pair));
    }
    return T_HASHMAP_SUCCESS;
}

double _t_HashMap_loadFactor(const T_HashMap *hashmap)
{
    if (hashmap->bucketsLength > 0)
    {
        return (double)hashmap->size / hashmap->bucketsLength;
    }
    else
    {
        return 0;
    }
}

int _t_HashMap_expand(T_HashMap *hashmap)
{
    size_t new_size = hashmap->bucketsLength * T_HASHMAP_GROW_RATE / 100;
    T_HashMap tempHash;
    tempHash.bucketsLength = new_size;
    tempHash.size = 0;
    tempHash.equalFunc = hashmap->equalFunc;
    tempHash.hashFunc = hashmap->hashFunc;
    tempHash.key_typeSize = hashmap->key_typeSize;
    tempHash.value_typeSize = hashmap->value_typeSize;
    tempHash.bucket_typeSize = hashmap->bucket_typeSize;
    struct T_HashMap_Bucket *new_location = malloc(new_size * hashmap->bucket_typeSize);
    if (new_location == NULL)
    {
        fprintf(stderr, "Error: Failed to reallocate memory for expand.\n");

        return T_HASHMAP_ERROR;
    }
    tempHash.buckets = new_location;
    _t_hashmap_init_buckets(&tempHash);

    _t_hashMap_Rehashing(hashmap, &tempHash);

    hashmap->bucketsLength = new_size;
    hashmap->buckets = tempHash.buckets;

    return T_HASHMAP_SUCCESS;
}

T_Pair *_t_hashmap_findPair(T_HashMap *hashmap, void *key)
{
    unsigned long hashKey = hashmap->hashFunc(key);
    size_t hashIndex = hashKey % hashmap->bucketsLength;
    T_Vector *targetBucket = &(hashmap->buckets[hashIndex].vector);

    for (size_t i = 0; i < targetBucket->size; i++)
    {
        if (hashmap->equalFunc(key, ((T_Pair *)targetBucket->data)->first))
        {
            return ((T_Pair *)targetBucket->data);
        }
    }
    return NULL;
}

int _t_hashMap_Rehashing(T_HashMap *source, T_HashMap *destination)
{
    for (size_t i = 0; i < source->bucketsLength; i++)
    {
        for (size_t j = 0; j < source->buckets[i].vector.size; j++)
        {
            T_Pair pair = T_VECTOR_GET_VALUE_AS(T_Pair, &source->buckets[i].vector, j);
            if (t_hashmap_assign(destination, pair.first, pair.second) == T_HASHMAP_ERROR)
            {
                return T_HASHMAP_ERROR;
            }
        }
    }

    _t_hashmap_destroy_withoutPair(source);
    return T_HASHMAP_SUCCESS;
}

void _t_hashmap_destroy_withoutPair(T_HashMap *hashmap)
{
    assert(hashmap != NULL);

    for (size_t i = 0; i < hashmap->bucketsLength; i++)
    {
        T_Vector *vector = &(hashmap->buckets[i].vector);
        t_vector_destroy(vector);
    }
    free(hashmap->buckets);
}

// T_HashMap_Iterator t_hashmap_iter_begin(const T_HashMap *hashmap)
// {
//     assert(hashmap != NULL);

//     T_HashMap_Iterator iterator;
//     iterator.hashmap = hashmap;
//     iterator.bucketPointer = hashmap->buckets;
//     T_Iterator valueIter = {iterator.bucketPointer->vector.data, hashmap->buckets->vector.typeSize};
//     iterator.valuePointer = valueIter;
//     _t_hashmap_iter_toNextData(&iterator);
//     printf("find begin\n");
//     return iterator;
// }

// T_HashMap_Iterator t_hashmap_iter_next(T_HashMap_Iterator *iterator)
// {
//     assert(iterator != NULL);
//     printf("value curr: %d\n", iterator->valuePointer.pointer);
//     printf("typeSize: %d\n", iterator->valuePointer.typeSize);
//     printf("size: %d\n", iterator->bucketPointer->vector.size);
//     printf("(%d, %d)\n", *(int *)((T_Pair *)(iterator->valuePointer.pointer))->first, *(int *)((T_Pair *)(iterator->valuePointer.pointer))->second);
//     printf("(%d, %d)\n", *(int *)((T_Pair *)(iterator->bucketPointer->vector.data))->first, *(int *)((T_Pair *)(iterator->bucketPointer->vector.data))->second);
//     t_vector_iter_next(&(iterator->valuePointer));
//     printf("after value curr: %d\n", iterator->valuePointer.pointer);
//     printf("curr bucket: %d\n", iterator->bucketPointer->vector.data);
//     printf("TypeSize: %d\n", iterator->bucketPointer->vector.typeSize);
//     printf("value end: %d\n", t_vector_iter_end(&(iterator->bucketPointer->vector)).pointer);
//     printf("expect end %d\n", iterator->bucketPointer->vector.data + iterator->bucketPointer->vector.size * iterator->bucketPointer->vector.typeSize);
//     if (iterator->valuePointer.pointer != t_vector_iter_end(&(iterator->bucketPointer->vector)).pointer)
//     {
//         printf("test12\n");
//         return *iterator;
//     }
//     printf("test13\n");
//     _t_hashmap_iter_toNextData(iterator);

//     return *iterator;
// }
// void _t_hashmap_iter_toNextData(T_HashMap_Iterator *iterator)
// {
//     assert(iterator != NULL);

//     printf("======================= start while\n");
//     while (iterator->bucketPointer != _t_hashMap_bucket_iter_end(iterator->hashmap) && iterator->valuePointer.pointer == t_vector_iter_end(&(iterator->bucketPointer->vector)).pointer)
//     {
//         printf("inside while\n");
//         printf("before now %d\n", iterator->bucketPointer);
//         printf("size: %d\n", iterator->bucketPointer->vector.size);
//         printf("cap: %d\n", iterator->bucketPointer->vector.capacity);
//         printf("value before: %d \n", t_vector_iter_begin(&(iterator->bucketPointer->vector)).pointer);
//         _t_hashMap_bucket_next(iterator);
//         printf("now %d\n", iterator->bucketPointer);
//         printf("end %d\n", _t_hashMap_bucket_iter_end(iterator->hashmap));
//         if (iterator->bucketPointer == _t_hashMap_bucket_iter_end(iterator->hashmap))
//         {
//             printf("werid\n");
//             T_Iterator nullIter = {NULL, 0};
//             iterator->valuePointer = nullIter;
//             return;
//         }
//         printf("value pre: %d\n", iterator->valuePointer);

//         iterator->valuePointer = t_vector_iter_begin(&(iterator->bucketPointer->vector));
//         printf("value post: %d\n", iterator->valuePointer);
//     }
//     printf("======================= finished while\n");
// }

// struct T_HashMap_Bucket *_t_hashMap_bucket_iter_begin(const T_HashMap *hashmap)
// {
//     assert(hashmap->buckets != NULL);

//     return hashmap->buckets;
// }
// struct T_HashMap_Bucket *_t_hashMap_bucket_iter_end(const T_HashMap *hashmap)
// {
//     assert(hashmap->buckets != NULL);

//     return hashmap->buckets + hashmap->bucketsLength * hashmap->bucket_typeSize;
// }

// void _t_hashMap_bucket_next(T_HashMap_Iterator *iterator)
// {
//     printf("--------------------- d\n");
//     assert(iterator != NULL);
//     iterator->bucketPointer += sizeof(struct T_HashMap_Bucket);
// }