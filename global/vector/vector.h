#ifndef TIN_VECTOR
#define TIN_VECTOR

#include <stddef.h>
#include "../utilities/func.h"
// Vector Type
typedef struct T_Vector
{
	void *data;
	size_t typeSize;

	size_t capacity;
	size_t size;

	size_t growCond;
	size_t growRate;

	size_t shrinkCond;
	size_t shrinkRate;

	size_t (*getSize)(const struct T_Vector *vector);
} T_Vector;
// Vector_Iterator Type
typedef struct T_Iterator
{
	void *pointer;
	size_t typeSize;
} T_Iterator;

// Constructor and Destructor
T_Vector t_vector_init(size_t typeSize);
T_Vector t_vector_custom_init(size_t typeSize, size_t capacity, size_t growCond, size_t growRate, size_t shrinkCond, size_t shrinkRate);
T_Vector t_vector_clone(const T_Vector *vector);
void t_vector_destroy(T_Vector *vector);

// Get Vector details

size_t t_vector_get_size(const T_Vector *vector);
size_t t_vector_get_capacity(const T_Vector *vector);
size_t t_vector_get_typeSize(const T_Vector *vector);
size_t t_vector_get_growCond(const T_Vector *vector);
size_t t_vector_get_growRate(const T_Vector *vector);
size_t t_vector_get_shrinkCond(const T_Vector *vector);
size_t t_vector_get_shrinkRate(const T_Vector *vector);

// Add & remove item
int t_vector_push_back(T_Vector *vector, void *element);
int t_vector_push_front(T_Vector *vector, void *element);
int t_vector_insert(T_Vector *vector, void *element, T_Iterator iterator);
int t_vector_pop_back(T_Vector *vector);
int t_vector_pop_front(T_Vector *vector);
int t_vector_erase(T_Vector *vector, T_Iterator iterator);

// Memory management
int t_vector_resize(T_Vector *vector, size_t size);
int t_vector_clear(T_Vector *vector);

// Iterator functions
T_Iterator t_vector_iter_begin(const T_Vector *vector);
T_Iterator t_vector_iter_end(const T_Vector *vector);
T_Iterator t_vector_iter_at(const T_Vector *vector, size_t index);
void t_vector_iter_next(T_Iterator *iterator);
void t_vector_iter_previous(T_Iterator *iterator);

// Display
void t_vector_display(const T_Vector *vector, T_DisplayFunc displayFunc);

// Private functions
size_t
_t_vector_offset(const T_Vector *vector, T_Iterator iterator);
int _t_vector_growable(const T_Vector *vector);
int _t_vector_expand(T_Vector *vector);
int _t_vector_move_right(T_Vector *vector, T_Iterator iterator);
int _t_vector_move_left(T_Vector *vector, T_Iterator iterator);

// Utility macros
#define T_VECTOR_NEW(type) t_vector_init(sizeof(type))
#define T_VECTOR_FOR_EACH(iterator, vector) \
	for (T_Iterator iterator = t_vector_iter_begin(vector); iterator.pointer < t_vector_iter_end(vector).pointer; t_vector_iter_next(&iterator))
#define T_VECTOR_ITERATOR_AS(type, iterator) ((type *)iterator.pointer)
#define T_VECTOR_ITERATOR_VALUE_AS(type, iterator) *((type *)(iterator.pointer))
#define T_VECTOR_GET_VALUE_AS(type, vector, index) T_VECTOR_ITERATOR_VALUE_AS(type, t_vector_iter_at(vector, index))

#endif