#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

T_Vector t_vector_init(int typeSize)
{
    T_Vector vector;
    vector.data = malloc(T_VECTOR_DEFAULT_CAPACITY * typeSize);
    if (vector.data == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for vector data.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }

    vector.capacity = T_VECTOR_DEFAULT_CAPACITY;
    vector.size = 0;
    vector.typeSize = typeSize;
    return vector;
}

T_Vector t_vector_clone(const T_Vector *vector)
{
    T_Vector clone_ventor;
    assert(vector != NULL);

    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    clone_ventor.data = malloc(vector->capacity * vector->typeSize);
    if (clone_ventor.data == NULL)
    {
        printf("\x1B[31m"
               "Failed to allocate memory for vector data.\n"
               "\x1B[0m");
        exit(EXIT_FAILURE);
    }
    memcpy(clone_ventor.data, vector->data, vector->size * vector->typeSize);
    clone_ventor.size = vector->size;
    clone_ventor.capacity = vector->capacity;
    clone_ventor.typeSize = vector->typeSize;

    return clone_ventor;
}

int t_vector_push_back(T_Vector *vector, void *element)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }

    if (_t_vector_growable(vector) == 0)
    {
        if (_t_vector_expand(vector) == T_VECTOR_ERROR)
        {
            return T_VECTOR_ERROR;
        }
    }

    void *offset = _t_vector_offset(vector, vector->size);
    if (offset == NULL)
    {
        return T_VECTOR_ERROR;
    }
    memcpy(offset, element, vector->typeSize);
    vector->size++;
    return T_VECTOR_SUCCESS;
}

void *t_vector_get(const T_Vector *vector, size_t index)
{
    if (index >= vector->size)
    {
        printf("\x1B[31m"
               "Index out of bounds. size: %d\n"
               "\x1B[0m",
               vector->size);
        return NULL;
    }
    return vector->data + index * vector->typeSize;
}

int t_vector_push_front(T_Vector *vector, void *element)
{
    return t_vector_insert(vector, element, 0);
}

int t_vector_insert(T_Vector *vector, void *element, size_t index)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }

    if (_t_vector_growable(vector) == 0)
    {
        if (_t_vector_expand(vector) == T_VECTOR_ERROR)
        {
            return T_VECTOR_ERROR;
        }
    }
    if (_t_vector_move_right(vector, index) == T_VECTOR_ERROR)
    {
        return T_VECTOR_ERROR;
    }
    void *offset = _t_vector_offset(vector, index);
    if (offset == NULL)
    {
        return T_VECTOR_ERROR;
    }
    memcpy(offset, element, vector->typeSize);
    vector->size++;
    return T_VECTOR_SUCCESS;
}

int t_vector_pop_back(T_Vector *vector)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }

    if (vector->size == 0)
    {
        return T_VECTOR_ERROR;
    }
    vector->size--;
    return T_VECTOR_SUCCESS;
}

int t_vector_pop_front(T_Vector *vector)
{
    return t_vector_erase(vector, 0);
}

int t_vector_erase(T_Vector *vector, size_t index)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }

    if (vector->size == 0)
    {
        return T_VECTOR_ERROR;
    }
    if (_t_vector_move_left(vector, index) == T_VECTOR_ERROR)
    {
        return T_VECTOR_ERROR;
    }
    vector->size--;
    return T_VECTOR_SUCCESS;
}

int t_vector_resize(T_Vector *vector, size_t size)
{
    assert(vector != NULL);
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

void *_t_vector_offset(const T_Vector *vector, int index)
{
    if (index > vector->size)
    {
        printf("\x1B[31m"
               "Index out of bounds. size: %d\n"
               "\x1B[0m",
               vector->size);
        return NULL;
    }
    return vector->data + index * vector->typeSize;
}

int _t_vector_growable(const T_Vector *vector)
{
    if (vector->size == vector->capacity)
    {
        return 0;
    }
    return 1;
}

int _t_vector_expand(T_Vector *vector)
{
    assert(vector != NULL);
    if (vector == NULL || vector->capacity == 0)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }

    void *new_location = realloc(vector->data, vector->capacity * T_VECTOR_GROW_RATE * vector->typeSize);
    if (new_location == NULL)
    {
        return T_VECTOR_ERROR;
    }
    vector->capacity *= T_VECTOR_GROW_RATE;
    vector->data = new_location;
    return T_VECTOR_SUCCESS;
}

int _t_vector_move_right(T_Vector *vector, size_t index)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }
    void *offset = _t_vector_offset(vector, index);
    if (offset == NULL)
    {
        return T_VECTOR_ERROR;
    }
    memcpy(offset + vector->typeSize, offset, (vector->size - index) * vector->typeSize);
    return T_VECTOR_SUCCESS;
}

int _t_vector_move_left(T_Vector *vector, size_t index)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        return T_VECTOR_ERROR;
    }
    void *offset = _t_vector_offset(vector, index);
    if (offset == NULL)
    {
        return T_VECTOR_ERROR;
    }
    memcpy(offset, offset + vector->typeSize, (vector->size - index - 1) * vector->typeSize);
    return T_VECTOR_SUCCESS;
}

T_Iterator t_vector_begin(const T_Vector *vector)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        T_Iterator nullIter = {NULL, 0};
        return nullIter;
    }
    T_Iterator iter;
    iter.pointer = vector->data;
    iter.typeSize = vector->typeSize;
    return iter;
}
T_Iterator t_vector_end(const T_Vector *vector)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        T_Iterator nullIter = {NULL, 0};
        return nullIter;
    }

    T_Iterator iter;
    iter.pointer = vector->data + (vector->size * vector->typeSize);
    iter.typeSize = vector->typeSize;
    return iter;
}

T_Iterator t_vector_iter_get(const T_Vector *vector, size_t index)
{
    assert(vector != NULL);
    if (vector == NULL)
    {
        printf("\x1B[31m"
               "Vector is null\n"
               "\x1B[0m");
        T_Iterator nullIter = {NULL, 0};
        return nullIter;
    }

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
    iterator->pointer += iterator->typeSize;
}
void t_vector_iter_previous(T_Iterator *iterator)
{
    iterator->pointer -= iterator->typeSize;
}

void t_vector_destroy(T_Vector *vector)
{
    if (vector != NULL)
    {
        free(vector->data);
        vector->data = NULL;
    }
}