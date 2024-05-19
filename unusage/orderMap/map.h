#ifndef T_MAP
#include "../utilities/func.h"
#include "../pair/pair.h"
#include <stddef.h>

typedef struct T_OrderMap
{
    struct T_OrderMap_Node *head;
    T_CompareFunc compareFunc;
    T_EqualFunc equalFunc;
    size_t key_typeSize;
    size_t value_typeSize;
    size_t size;
} T_OrderMap;

struct T_OrderMap_Node
{
    T_Pair data;
    struct T_OrderMap_Node *parent;
    struct T_OrderMap_Node *left;
    struct T_OrderMap_Node *right;
};

T_OrderMap t_ordermap_init(size_t key_typeSize, size_t value_typeSize, T_CompareFunc compareFunc, T_EqualFunc equalFunc);
void t_ordermap_destroy(T_OrderMap *map);

void *t_ordermap_find(const T_OrderMap *map, void *key);
int t_ordermap_insert(T_OrderMap *map, void *key, void *value);
int t_ordermap_edit(T_OrderMap *map, void *key, void *value);
int t_ordermap_erase(T_OrderMap *map, void *key);

// Getter
T_Pair *t_ordermap_min(const T_OrderMap *map);
T_Pair *t_ordermap_max(const T_OrderMap *map);
size_t t_ordermap_get_size(const T_OrderMap *map);
size_t t_ordermap_get_height(const T_OrderMap *map);

// Display
const void t_ordermap_display(const T_OrderMap *map, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);
const void t_ordermap_displayBreadth(const T_OrderMap *map, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);

#define T_ORDERMAP_NEW_INT_INT() t_ordermap_init(sizeof(int), sizeof(int), t_utilities_compareInt, t_utilities_equalInt)
#define T_ORDERMAP_NEW_STRING_STRING() t_ordermap_init(sizeof(char *), sizeof(char *), t_utilities_compareString, t_utilities_equalString)
#define T_ORDERMAP_NEW_INT_STRING() t_ordermap_init(sizeof(int), sizeof(char *), t_utilities_compareInt, t_utilities_equalInt)
#define T_ORDERMAP_NEW_STRING_INT() t_ordermap_init(sizeof(char *), sizeof(int), t_utilities_compareString, t_utilities_equalString)

#endif
