#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../queue/queue.h"

#define T_ORDERMAP_ERROR 1
#define T_ORDERMAP_SUCCESS 0

// Private

struct T_OrderMap_Node *_t_ordermap_initNode(const T_OrderMap *map, void *key, void *value);
struct T_OrderMap_Node *_t_ordermap_findEqualNode(const T_OrderMap *map, struct T_OrderMap_Node *node, void *key);
struct T_OrderMap_Node *_t_ordermap_findParentNode(const T_OrderMap *map, struct T_OrderMap_Node *node, void *key);
struct T_OrderMap_Node *_t_ordermap_findMaxNode(const T_OrderMap *map, struct T_OrderMap_Node *node);
struct T_OrderMap_Node *_t_ordermap_findMinNode(const T_OrderMap *map, struct T_OrderMap_Node *node);
const void _t_ordermap_displayNodeMaxToMin(struct T_OrderMap_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);
const void _t_ordermap_displayNodeBreadth(struct T_OrderMap_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);
const void _t_ordermap_destroyNode(struct T_OrderMap_Node *node);
size_t _t_ordermap_get_height_Node(struct T_OrderMap_Node *node);

T_OrderMap t_ordermap_init(size_t key_typeSize, size_t value_typeSize, T_CompareFunc compareFunc, T_EqualFunc equalFunc)
{
    assert(compareFunc != NULL);
    assert(equalFunc != NULL);
    assert(key_typeSize > 0);
    assert(value_typeSize > 0);

    T_OrderMap map;
    map.compareFunc = compareFunc;
    map.equalFunc = equalFunc;
    map.head = NULL;
    map.key_typeSize = key_typeSize;
    map.value_typeSize = value_typeSize;
    map.size = 0;
    return map;
}

void t_ordermap_destroy(T_OrderMap *map)
{
    assert(map != NULL);
    _t_ordermap_destroyNode(map->head);
    map->compareFunc = NULL;
    map->equalFunc = NULL;
    map->head = NULL;
    map->key_typeSize = 0;
    map->size = 0;
    map->value_typeSize = 0;
}

int t_ordermap_insert(T_OrderMap *map, void *key, void *value)
{
    assert(map != NULL);
    assert(map->compareFunc != NULL);
    assert(map->equalFunc != NULL);
    assert(map->key_typeSize > 0);
    assert(map->value_typeSize > 0);
    assert(key != NULL);
    assert(value != NULL);

    if (_t_ordermap_findEqualNode(map, map->head, key) != NULL)
    {
        printf("\x1B[31m"
               "The key is already in map\n"
               "\x1B[0m");
        return T_ORDERMAP_ERROR;
    }
    struct T_OrderMap_Node *parent = _t_ordermap_findParentNode(map, map->head, key);
    if (parent == NULL)
    {
        parent = _t_ordermap_initNode(map, key, value);
        map->head = parent;
    }
    else
    {
        struct T_OrderMap_Node *node = _t_ordermap_initNode(map, key, value);
        if (node == NULL)
        {
            printf("\x1B[31m"
                   "Error to create Node\n"
                   "\x1B[0m");
            return T_ORDERMAP_ERROR;
        }
        if (map->compareFunc(parent->data.first, key))
        {
            parent->left = node;
            node->parent = parent;
        }
        else
        {
            parent->right = node;
            node->parent = parent;
        }
    }

    map->size++;
    return T_ORDERMAP_SUCCESS;
}

void *t_ordermap_find(const T_OrderMap *map, void *key)
{
    assert(map != NULL);
    assert(key != NULL);

    struct T_OrderMap_Node *targetNode = _t_ordermap_findEqualNode(map, map->head, key);
    if (targetNode == NULL)
    {
        return NULL;
    }
    return targetNode->data.second;
}

int t_ordermap_edit(T_OrderMap *map, void *key, void *value)
{
    assert(map != NULL);
    assert(key != NULL);
    assert(value != NULL);

    struct T_OrderMap_Node *target = _t_ordermap_findEqualNode(map, map->head, key);
    if (target == NULL)
    {
        printf("\x1B[31m"
               "The key does not be found in the map\n"
               "\x1B[0m");
        return T_ORDERMAP_ERROR;
    }
    if (T_pair_setSecond(&target->data, value, map->value_typeSize) == 1)
    {
        return T_ORDERMAP_ERROR;
    }
    return T_ORDERMAP_SUCCESS;
}

int t_ordermap_erase(T_OrderMap *map, void *key)
{
    assert(map != NULL);
    assert(key != NULL);

    struct T_OrderMap_Node *target = _t_ordermap_findEqualNode(map, map->head, key);
    if (target == NULL)
    {
        printf("\x1B[31m"
               "The key does not exist in the map\n"
               "\x1B[0m");
        return T_ORDERMAP_ERROR;
    }

    if (target == map->head)
    {
        if (target->left == NULL && target->right == NULL)
        {
            T_pair_destroy(&target->data);
            map->head = NULL;
        }
        else if (target->left != NULL && target->right != NULL)
        {
            struct T_OrderMap_Node *max_left = _t_ordermap_findMaxNode(map, target->left);
            struct T_OrderMap_Node *min_right = _t_ordermap_findMinNode(map, target->right);
            if (map->compareFunc(max_left->data.first, min_right->data.first))
            {
                map->head = target->left;
                max_left->right = target->right;
                target->right->parent = max_left;
            }
            else
            {
                map->head = target->right;
                min_right->left = target->left;
                target->left->parent = min_right;
            }
            T_pair_destroy(&target->data);
        }
        else
        {
            struct T_OrderMap_Node *child = target->left != NULL ? target->left : target->right;
            map->head = child;
            child->parent = NULL;
            T_pair_destroy(&target->data);
        }
    }
    else
    {
        struct T_OrderMap_Node *parent_child = target->parent->left == target ? target->parent->left : target->parent->right;
        if (target->left == NULL && target->right == NULL)
        {
            parent_child = NULL;
            T_pair_destroy(&target->data);
        }
        else if (target->left != NULL && target->right != NULL)
        {
            struct T_OrderMap_Node *max_left = _t_ordermap_findMaxNode(map, target->left);
            struct T_OrderMap_Node *min_right = _t_ordermap_findMinNode(map, target->right);
            if (map->compareFunc(max_left->data.first, min_right->data.first))
            {
                parent_child = target->left;
                max_left->right = target->right;
                target->right->parent = max_left;
            }
            else
            {
                parent_child = target->right;
                min_right->left = target->left;
                target->left->parent = min_right;
            }
            T_pair_destroy(&target->data);
        }
        else
        {
            struct T_OrderMap_Node *child = target->left != NULL ? target->left : target->right;
            parent_child = child;
            child->parent = target->parent;
            T_pair_destroy(&target->data);
        }
    }

    map->size--;
    return T_ORDERMAP_SUCCESS;
}

T_Pair *t_ordermap_min(const T_OrderMap *map)
{
    assert(map != NULL);
    if (map->size == 0)
    {
        printf("\x1B[31m"
               "The map is empty.\n"
               "\x1B[0m");
        return NULL;
    }
    return &_t_ordermap_findMinNode(map, map->head)->data;
}
T_Pair *t_ordermap_max(const T_OrderMap *map)
{
    assert(map != NULL);
    if (map->size == 0)
    {
        printf("\x1B[31m"
               "The map is empty.\n"
               "\x1B[0m");
        return NULL;
    }
    return &_t_ordermap_findMaxNode(map, map->head)->data;
}
const void t_ordermap_display(const T_OrderMap *map, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    printf("{ ");
    _t_ordermap_displayNodeMaxToMin(map->head, displayFunc1, displayFunc2);
    printf("}\n");
}

const void t_ordermap_displayBreadth(const T_OrderMap *map, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    printf("{ ");
    _t_ordermap_displayNodeBreadth(map->head, displayFunc1, displayFunc2);
    printf("}\n");
}

size_t t_ordermap_get_size(const T_OrderMap *map)
{
    assert(map != NULL);
    return map->size;
}
size_t t_ordermap_get_height(const T_OrderMap *map)
{
    assert(map != NULL);
    return _t_ordermap_get_height_Node(map->head);
}

struct T_OrderMap_Node *_t_ordermap_findMaxNode(const T_OrderMap *map, struct T_OrderMap_Node *node)
{
    if (node->right == NULL)
    {
        return node;
    }
    return _t_ordermap_findMaxNode(map, node->right);
}
struct T_OrderMap_Node *_t_ordermap_findMinNode(const T_OrderMap *map, struct T_OrderMap_Node *node)
{
    if (node->left == NULL)
    {
        return node;
    }
    return _t_ordermap_findMinNode(map, node->left);
}

struct T_OrderMap_Node *_t_ordermap_initNode(const T_OrderMap *map, void *key, void *value)
{
    struct T_OrderMap_Node *node = malloc(sizeof(struct T_OrderMap_Node));
    if (node == NULL)
    {
        return NULL;
    }

    node->data = T_pair_init_with(key, map->key_typeSize, value, map->value_typeSize);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

struct T_OrderMap_Node *_t_ordermap_findEqualNode(const T_OrderMap *map, struct T_OrderMap_Node *node, void *key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (map->equalFunc(node->data.first, key))
    {
        return node;
    }
    struct T_OrderMap_Node *foundNode = _t_ordermap_findEqualNode(map, node->left, key);
    if (foundNode == NULL)
    {
        foundNode = _t_ordermap_findEqualNode(map, node->right, key);
    }
    return foundNode;
}
struct T_OrderMap_Node *_t_ordermap_findParentNode(const T_OrderMap *map, struct T_OrderMap_Node *node, void *key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (map->compareFunc(node->data.first, key))
    {
        if (node->left == NULL)
        {
            return node;
        }
        return _t_ordermap_findParentNode(map, node->left, key);
    }
    else
    {
        if (node->right == NULL)
        {
            return node;
        }
        return _t_ordermap_findParentNode(map, node->right, key);
    }
}

const void _t_ordermap_displayNodeMaxToMin(struct T_OrderMap_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    if (node->left != NULL)
    {
        _t_ordermap_displayNodeMaxToMin(node->left, displayFunc1, displayFunc2);
    }
    t_pair_display(&node->data, displayFunc1, displayFunc2);
    printf(" ");
    if (node->right != NULL)
    {
        _t_ordermap_displayNodeMaxToMin(node->right, displayFunc1, displayFunc2);
    }
}

const void _t_ordermap_displayNodeBreadth(struct T_OrderMap_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    T_Queue queue = T_QUEUE_NEW(struct T_OrderMap_Node);
    t_queue_enqueue(&queue, node);
    struct T_OrderMap_Node *current;
    while (!t_queue_isEmpty(&queue))
    {
        current = t_queue_front(&queue);
        if (current != NULL)
            t_pair_display(&current->data, displayFunc1, displayFunc2);
        {
            if (current->left != NULL)
            {
                t_queue_enqueue(&queue, current->left);
            }
            if (current->right != NULL)
            {
                t_queue_enqueue(&queue, current->right);
            }

            printf(" ");
        }
        t_queue_dequeue(&queue);
    }
    t_queue_destroy(&queue);
}

const void _t_ordermap_destroyNode(struct T_OrderMap_Node *node)
{
    if (node->left != NULL)
    {
        _t_ordermap_destroyNode(node->left);
    }
    if (node->right != NULL)
    {
        _t_ordermap_destroyNode(node->right);
    }
    T_pair_destroy(&node->data);
    free(node);
}

size_t _t_ordermap_get_height_Node(struct T_OrderMap_Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    size_t left_height = _t_ordermap_get_height_Node(node->left);
    size_t right_height = _t_ordermap_get_height_Node(node->right);
    return 1 + left_height > right_height ? left_height : right_height;
}