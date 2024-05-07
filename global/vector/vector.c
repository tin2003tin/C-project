#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define T_VECTOR_DEFAULT_SIZE 0
#define T_VECTOR_DEFAULT_CAPACITY 1

#define T_VECTOR_GROW_COND 100
#define T_VECTOR_GROW_RATE 200

#define T_VECTOR_SHRINK_COND 0
#define T_VECTOR_SHRINK_RATE 0

#define T_VECTOR_ERROR 1
#define T_VECTOR_SUCCESS 0

T_Vector t_vector_init(size_t typeSize)
{
    return t_vector_custom_init(typeSize, T_VECTOR_DEFAULT_CAPACITY, T_VECTOR_GROW_COND, T_VECTOR_GROW_RATE, T_VECTOR_SHRINK_COND, T_VECTOR_SHRINK_RATE);
}

T_Vector t_vector_custom_init(size_t typeSize, size_t capacity, size_t growCond, size_t growRate, size_t shrinkCond, size_t shrinkRate)
{
    if (capacity == 0)
    {
        printf("\x1B[31m"
               "Capacity must be greater than 0.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (growCond > 100)
    {
        printf("\x1B[31m"
               "GrowCond must be lower than 100.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (growRate < 100)
    {
        printf("\x1B[31m"
               "GrowRate must be greater than 100.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (shrinkCond > 100)
    {
        printf("\x1B[31m"
               "ShrinkCond must be lower than 100.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    if (shrinkRate > 100)
    {
        printf("\x1B[31m"
               "ShrinkRate must be lower than 100.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    T_Vector vector;

    vector.data = malloc(capacity * typeSize);
    if (vector.data == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for vector data.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    vector.typeSize = typeSize;
    vector.capacity = capacity;
    vector.size = 0;
    vector.growCond = growCond;
    vector.growRate = growRate;
    vector.shrinkCond = shrinkCond;
    vector.shrinkRate = shrinkRate;

    return vector;
}
T_Vector t_vector_clone(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    T_Vector clone_vector = *vector;
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for vector.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }

    clone_vector.data = malloc(vector->capacity * vector->typeSize);
    if (clone_vector.data == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for vector data.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }

    memcpy(clone_vector.data, vector->data, vector->size * vector->typeSize);
    return clone_vector;
}

void t_vector_destroy(T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    free(vector->data);
    vector->data = NULL;
    vector->capacity = 0;
    vector->size = 0;
    vector->growCond = 0;
    vector->growRate = 0;
    vector->shrinkCond = 0;
    vector->shrinkRate = 0;
}

size_t t_vector_get_size(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    return vector->size;
}
size_t t_vector_get_capacity(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    return vector->capacity;
}
size_t t_vector_get_typeSize(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    return vector->typeSize;
}
size_t t_vector_get_growCond(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    return vector->growCond;
}
size_t t_vector_get_growRate(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    return vector->growRate;
}
size_t t_vector_get_shrinkCond(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    return vector->shrinkCond;
}
size_t t_vector_get_shrinkRate(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    return vector->shrinkRate;
}

int t_vector_push_back(T_Vector *vector, void *element)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    size_t offset = _t_vector_offset(vector, t_vector_iter_end(vector));
    if (offset == SIZE_MAX)
    {
        return T_VECTOR_ERROR;
    }

    if (_t_vector_growable(vector) == 1)
    {
        if (_t_vector_expand(vector) == T_VECTOR_ERROR)
        {
            return T_VECTOR_ERROR;
        }
    }

    memcpy(vector->data + offset, element, vector->typeSize);
    vector->size++;
    return T_VECTOR_SUCCESS;
}

int t_vector_push_front(T_Vector *vector, void *element)
{
    return t_vector_insert(vector, element, t_vector_iter_begin(vector));
}

int t_vector_insert(T_Vector *vector, void *element, T_Iterator iterator)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    size_t offset = _t_vector_offset(vector, iterator);
    if (offset == SIZE_MAX)
    {
        return T_VECTOR_ERROR;
    }

    if (_t_vector_growable(vector) == 1)
    {
        if (_t_vector_expand(vector) == T_VECTOR_ERROR)
        {
            return T_VECTOR_ERROR;
        }
    }
    if (_t_vector_move_right(vector, iterator) == T_VECTOR_ERROR)
    {
        return T_VECTOR_ERROR;
    }

    memcpy(vector->data + offset, element, vector->typeSize);
    vector->size++;
    return T_VECTOR_SUCCESS;
}

int t_vector_pop_back(T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    if (vector->size == 0)
    {
        return T_VECTOR_ERROR;
    }
    vector->size--;
    return T_VECTOR_SUCCESS;
}

int t_vector_pop_front(T_Vector *vector)
{
    return t_vector_erase(vector, t_vector_iter_begin(vector));
}

int t_vector_erase(T_Vector *vector, T_Iterator iterator)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    if (vector->size == 0)
    {
        return T_VECTOR_ERROR;
    }
    if (_t_vector_move_left(vector, iterator) == T_VECTOR_ERROR)
    {
        return T_VECTOR_ERROR;
    }
    vector->size--;
    return T_VECTOR_SUCCESS;
}

int t_vector_resize(T_Vector *vector, size_t size)
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }
    if (size > vector->capacity)
    {
        void *new_location = realloc(vector->data, size * vector->typeSize);
        if (new_location == NULL)
        {
            return T_VECTOR_ERROR;
        }
        vector->data = new_location;
        vector->capacity = size;
    }
    else
    {
        vector->capacity = size == 0 ? T_VECTOR_DEFAULT_CAPACITY : size;
        vector->size = size;
    }
    return T_VECTOR_SUCCESS;
}

int t_vector_clear(T_Vector *vector)
{
    return t_vector_resize(vector, 0);
}

void t_vector_display(const T_Vector *vector, const void (*displayFunc)(const void *))
{
    assert(vector != NULL);
    assert(vector->data != NULL);
    T_VECTOR_FOR_EACH(iter, vector)
    {
        displayFunc(iter.pointer);
    }
}

T_Iterator t_vector_iter_begin(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    T_Iterator iter;
    iter.pointer = vector->data;
    iter.typeSize = vector->typeSize;
    return iter;
}
T_Iterator t_vector_iter_end(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    T_Iterator iter;
    iter.pointer = vector->data + (vector->size * vector->typeSize);
    iter.typeSize = vector->typeSize;
    return iter;
}

T_Iterator t_vector_iter_at(const T_Vector *vector, size_t index)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    if (index >= vector->size)
    {
        printf("\x1B[31m"
               "Index out of bounds. size: %d\n"
               "\x1B[0m",
               vector->size);
        T_Iterator nullIter = {NULL, 0};
        return nullIter;
    }

    T_Iterator iter;
    iter.pointer = vector->data + (index * vector->typeSize);
    iter.typeSize = vector->typeSize;
    return iter;
}

void t_vector_iter_next(T_Iterator *iterator)
{
    assert(iterator != NULL);
    iterator->pointer += iterator->typeSize;
}
void t_vector_iter_previous(T_Iterator *iterator)
{
    assert(iterator != NULL);
    iterator->pointer -= iterator->typeSize;
}

size_t _t_vector_offset(const T_Vector *vector, T_Iterator iterator)
{
    if (iterator.pointer < vector->data || iterator.pointer > vector->data + vector->size * vector->typeSize)
    {
        printf("\x1B[31m"
               "Iterator out of bounds.\n"
               "\x1B[0m");
        return SIZE_MAX;
    }
    return (size_t)((char *)iterator.pointer - (char *)vector->data);
}

int _t_vector_growable(const T_Vector *vector)
{
    if (vector->size == vector->capacity * (vector->growCond) / 100)
    {
        return 1;
    }
    return 0;
}

int _t_vector_expand(T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    void *new_location = realloc(vector->data, (vector->capacity * vector->growRate * vector->typeSize) / 100);
    if (new_location == NULL)
    {
        printf("\x1B[31m"
               "Failed to reallocate memory for expand.\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }

    vector->capacity = (vector->capacity * vector->growRate) / 100;
    vector->data = new_location;
    return T_VECTOR_SUCCESS;
}

int _t_vector_move_right(T_Vector *vector, T_Iterator iterator)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    size_t offset = _t_vector_offset(vector, iterator);
    if (offset == SIZE_MAX)
    {
        return T_VECTOR_ERROR;
    }
    memcpy(vector->data + offset + vector->typeSize, vector->data + offset, vector->size * vector->typeSize - offset);
    return T_VECTOR_SUCCESS;
}

int _t_vector_move_left(T_Vector *vector, T_Iterator iterator)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    size_t offset = _t_vector_offset(vector, iterator);
    if (offset == SIZE_MAX)
    {
        return T_VECTOR_ERROR;
    }
    memcpy(vector->data + offset, vector->data + offset + vector->typeSize, (vector->size - 1) * vector->typeSize - offset);
    return T_VECTOR_SUCCESS;
}