#ifndef T_AVL_OrderMap
#include "../utilities/func.h"
#include "../pair/pair.h"
#include <stddef.h>

typedef struct T_OrderMap
{
    struct T_AVL_OrderMap_Node *head;
    T_CompareFunc compareFunc;
    T_EqualFunc equalFunc;
    size_t key_typeSize;
    size_t value_typeSize;
    size_t size;
} T_AVL_OrderMap;

struct T_AVL_OrderMap_Node
{
    T_Pair data;
    size_t height;
    struct T_AVL_OrderMap_Node *parent;
    struct T_AVL_OrderMap_Node *left;
    struct T_AVL_OrderMap_Node *right;
};

T_AVL_OrderMap t_AVL_ordermap_init(size_t key_typeSize, size_t value_typeSize, T_CompareFunc compareFunc, T_EqualFunc equalFunc);
void t_AVL_ordermap_destroy(T_AVL_OrderMap *map);

void *t_AVL_ordermap_find(const T_AVL_OrderMap *map, void *key);
int t_AVL_ordermap_insert(T_AVL_OrderMap *map, void *key, void *value);
int t_AVL_ordermap_edit(T_AVL_OrderMap *map, void *key, void *value);
int t_AVL_ordermap_erase(T_AVL_OrderMap *map, void *key);

// Getter
T_Pair *t_AVL_ordermap_min(const T_AVL_OrderMap *map);
T_Pair *t_AVL_ordermap_max(const T_AVL_OrderMap *map);
size_t t_AVL_ordermap_get_size(const T_AVL_OrderMap *map);
size_t t_AVL_ordermap_get_height(const T_AVL_OrderMap *map);

// Display
const void t_AVL_ordermap_display(const T_AVL_OrderMap *map, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);
const void t_AVL_ordermap_displayBreadth(const T_AVL_OrderMap *map, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);

#define T_AVL_ORDERMAP_NEW_INT_INT() t_AVL_ordermap_init(sizeof(int), sizeof(int), t_utilities_compareInt, t_utilities_equalInt)
#define T_AVL_ORDERMAP_NEW_STRING_STRING() t_AVL_ordermap_init(sizeof(char *), sizeof(char *), t_utilities_compareString, t_utilities_equalString)
#define T_AVL_ORDERMAP_NEW_INT_STRING() t_AVL_ordermap_init(sizeof(int), sizeof(char *), t_utilities_compareInt, t_utilities_equalInt)
#define T_AVL_ORDERMAP_NEW_STRING_INT() t_AVL_ordermap_init(sizeof(char *), sizeof(int), t_utilities_compareString, t_utilities_equalString)

#endif