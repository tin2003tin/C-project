#ifndef tin_Vector
#define tin_Vector
#include <stddef.h>

#define T_VECTOR_DEFAULT_SIZE 0
#define T_VECTOR_DEFAULT_CAPACITY 1
#define T_VECTOR_GROW_RATE 2
#define T_VECTOR_ERROR 1
#define T_VECTOR_SUCCESS 0

typedef struct
{
	void *data;
	size_t capacity;
	size_t size;
	size_t typeSize;
} T_Vector;

typedef struct
{
	void *pointer;
	size_t typeSize;
} T_Iterator;

// contructor
T_Vector t_vector_init(int typeSize);

// destructor
void t_vector_destroy(T_Vector *vector);

// add & remove Item
int t_vector_push_back(T_Vector *vector, void *element);
int t_vector_push_front(T_Vector *vector, void *element);
int t_vector_pop_back(T_Vector *vector);
int t_vector_pop_front(T_Vector *vector);
int t_vector_erase(T_Vector *vector, size_t index);
int t_vector_insert(T_Vector *vector, void *element, size_t index);

// iterator
T_Iterator t_vector_begin(const T_Vector *vector);
T_Iterator t_vector_end(const T_Vector *vector);
T_Iterator t_vector_iter_get(const T_Vector *vector, size_t index);
void t_vector_iter_next(T_Iterator *iterator);
void t_vector_iter_previous(T_Iterator *iterator);

// get
void *t_vector_get(const T_Vector *vector, size_t index);

// memory management
int t_vector_resize(T_Vector *vector, size_t size);
int t_vector_clear(T_Vector *vector);

// vector private
void *_t_vector_offset(T_Vector *vector, int index);
int _t_vector_growable(T_Vector *vector);
int _t_vector_expand(T_Vector *vector);
int _t_vector_move_right(T_Vector *vector, size_t index);
int _t_vector_move_left(T_Vector *vector, size_t index);

// utilities
#define T_VECTOR_NEW(type) t_vector_init(sizeof(type))
#define T_VECTOR_FOR_EACH(iterator, vector) \
	for (T_Iterator iterator = t_vector_begin(&vector); iterator.pointer < t_vector_end(&vector).pointer; t_vector_iter_next(&iter))
#define T_VECTOR_ITERATOR_AS(type, iterator) ((type *)iterator.pointer)
#define T_VECTOR_ITERATOR_VALUE_AS(type, iterator) *((type *)iterator.pointer)
#define T_VECTOR_GET_AS(type, vector, index) *(type *)(t_vector_get(&vector, index))


#endif
