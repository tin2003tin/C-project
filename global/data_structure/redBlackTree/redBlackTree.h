#ifndef T_REDBLACK_TREE
#define T_REDBLACK_TREE
#include <stddef.h>
#include <stdbool.h>
#include "../pair/pair.h"
#include "../utilities/func.h"

typedef struct T_RedBlack_Tree
{
    struct T_RedBlack_Node *head;
    size_t key_typeSize;
    size_t value_typeSize;
    size_t size;
    T_EqualFunc equalFunc;
    T_CompareFunc compareFunc;
} T_RedBlack_Tree;

struct T_RedBlack_Node
{
    T_Pair obj;
    bool isBlack;
    struct T_RedBlack_Node *parent;
    struct T_RedBlack_Node *left;
    struct T_RedBlack_Node *right;
};

T_RedBlack_Tree t_redblack_tree_init(size_t key_typeSize, size_t value_typeSize, T_CompareFunc compareFunc, T_EqualFunc equalFunc);
void t_redblack_tree_destroy(T_RedBlack_Tree *tree);

T_Pair *t_redblack_tree_min(const T_RedBlack_Tree *tree);
T_Pair *t_redblack_tree_max(const T_RedBlack_Tree *tree);
size_t t_redblack_tree_get_size(const T_RedBlack_Tree *tree);
size_t t_redblack_tree_get_height(const T_RedBlack_Tree *tree);

void *t_redblack_tree_find(const T_RedBlack_Tree *tree, void *key);
int t_redblack_tree_insert(T_RedBlack_Tree *tree, void *key, void *value);
int t_redblack_edit(T_RedBlack_Tree *tree, void *key, void *value);
int t_redblack_tree_remove(T_RedBlack_Tree *tree, void *key);

void t_redblack_display(const T_RedBlack_Tree *tree, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);
void t_redblack_displayBreadth(const T_RedBlack_Tree *tree, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);

#endif