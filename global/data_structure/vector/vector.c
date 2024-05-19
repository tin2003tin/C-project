#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define T_VECTOR_DEFAULT_SIZE 0
#define T_VECTOR_DEFAULT_CAPACITY 1

#define T_VECTOR_GROW_COND 100
#define T_VECTOR_GROW_RATE 200

#define T_VECTOR_ERROR 1
#define T_VECTOR_SUCCESS 0

// Private functions
size_t _t_vector_offset(const T_Vector *vector, T_Iterator iterator);
bool _t_vector_growable(const T_Vector *vector);
int _t_vector_expand(T_Vector *vector);
int _t_vector_move_right(T_Vector *vector, T_Iterator iterator);
int _t_vector_move_left(T_Vector *vector, T_Iterator iterator);

T_Vector t_vector_init(size_t typeSize)
{
    T_Vector vector;
    vector.data = NULL;
    vector.data = malloc(T_VECTOR_DEFAULT_CAPACITY * typeSize);
    if (vector.data == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for vector: %ld\n", T_VECTOR_DEFAULT_CAPACITY * typeSize);
        exit(EXIT_FAILURE);
    }
    vector.typeSize = typeSize;
    vector.capacity = T_VECTOR_DEFAULT_CAPACITY;
    vector.size = 0;

    return vector;
}
T_Vector t_vector_clone(const T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    T_Vector clone_vector = *vector;

    clone_vector.data = malloc(vector->capacity * vector->typeSize);
    if (clone_vector.data == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for vector\n");
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

int t_vector_push_back(T_Vector *vector, void *element)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    size_t offset = _t_vector_offset(vector, t_vector_iter_end(vector));

    if (offset == (size_t)-1)
    {
        return T_VECTOR_ERROR;
    }

    if (_t_vector_growable(vector))
    {
        if (_t_vector_expand(vector) == T_VECTOR_ERROR)
        {
            return T_VECTOR_ERROR;
        }
    }

    memcpy((char *)vector->data + offset, element, vector->typeSize);
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
    if (offset == (size_t)-1)
    {
        return T_VECTOR_ERROR;
    }

    if (_t_vector_growable(vector))
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

    memcpy((char *)vector->data + offset, element, vector->typeSize);
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

void t_vector_display(const T_Vector *vector, T_DisplayFunc displayFunc)
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

    T_Iterator iter;
    iter.pointer = vector->data;
    iter.typeSize = vector->typeSize;
    return iter;
}
T_Iterator t_vector_iter_end(const T_Vector *vector)
{
    assert(vector != NULL);

    T_Iterator iter;
    iter.pointer = (char *)vector->data + (vector->size * vector->typeSize);
    iter.typeSize = vector->typeSize;
    return iter;
}

T_Iterator t_vector_iter_at(const T_Vector *vector, size_t index)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    if (index >= vector->size)
    {
        fprintf(stderr, "Error: Index out of bounds. size: %ld\n", index);
        T_Iterator nullIter = {NULL, 0};
        return nullIter;
    }

    T_Iterator iter;
    iter.pointer = (char *)vector->data + (index * vector->typeSize);
    iter.typeSize = vector->typeSize;
    return iter;
}

void t_vector_iter_next(T_Iterator *iterator)
{
    assert(iterator != NULL);
    iterator->pointer = (char *)iterator->pointer + iterator->typeSize;
}
void t_vector_iter_previous(T_Iterator *iterator)
{
    assert(iterator != NULL);
    iterator->pointer = (char *)iterator->pointer - iterator->typeSize;
}

size_t _t_vector_offset(const T_Vector *vector, T_Iterator iterator)
{
    if (vector == NULL || vector->data == NULL || iterator.pointer == NULL)
    {
        fprintf(stderr, "Error: Invalid vector or iterator.\n");
        return (size_t)-1;
    }

    size_t offset = (size_t)((char *)iterator.pointer - (char *)vector->data);

    if (offset > vector->size * vector->typeSize)
    {
        fprintf(stderr, "Error: Iterator out of bounds.\n");
        return (size_t)-1;
    }

    return offset;
}

bool _t_vector_growable(const T_Vector *vector)
{
    if (vector->size == vector->capacity * (T_VECTOR_GROW_COND) / 100)
    {
        return true;
    }
    return false;
}

int _t_vector_expand(T_Vector *vector)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    void *new_location = realloc(vector->data, (vector->capacity * T_VECTOR_GROW_RATE * vector->typeSize) / 100);
    if (new_location == NULL)
    {
        fprintf(stderr, "Error: Failed to reallocate memory for expand.\n");
        return T_VECTOR_ERROR;
    }

    vector->capacity = (vector->capacity * T_VECTOR_GROW_RATE) / 100;
    vector->data = new_location;
    return T_VECTOR_SUCCESS;
}

int _t_vector_move_right(T_Vector *vector, T_Iterator iterator)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    size_t offset = _t_vector_offset(vector, iterator);
    if (offset == (size_t)-1)
    {
        return T_VECTOR_ERROR;
    }
    memcpy((char *)vector->data + offset + vector->typeSize, (char *)vector->data + offset, vector->size * vector->typeSize - offset);
    return T_VECTOR_SUCCESS;
}

int _t_vector_move_left(T_Vector *vector, T_Iterator iterator)
{
    assert(vector != NULL);
    assert(vector->data != NULL);

    size_t offset = _t_vector_offset(vector, iterator);
    if (offset == (size_t)-1)
    {
        return T_VECTOR_ERROR;
    }
    memcpy((char *)vector->data + offset, (char *)vector->data + offset + vector->typeSize, (vector->size - 1) * vector->typeSize - offset);
    return T_VECTOR_SUCCESS;
}