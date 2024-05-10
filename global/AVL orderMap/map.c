#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../queue/queue.h"

#define T_AVL_ORDERMAP_ERROR 1
#define T_AVL_ORDERMAP_SUCCESS 0

// Private

struct T_AVL_OrderMap_Node *_t_AVL_ordermap_initNode(const T_AVL_OrderMap *map, void *key, void *value);
struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findEqualNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node, void *key);
struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findParentNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node, void *key);
struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findMaxNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node);
struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findMinNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node);
const void _t_AVL_ordermap_displayNodeMaxToMin(struct T_AVL_OrderMap_Node *node, T_DisplayFunc displayFunc);
const void _t_AVL_ordermap_displayNodeBreadth(struct T_AVL_OrderMap_Node *node, T_DisplayFunc displayFunc);
const void _t_AVL_ordermap_destroyNode(struct T_AVL_OrderMap_Node *node);
int _t_AVL_ordermap_get_height_Node(struct T_AVL_OrderMap_Node *node);
void _t_AVL_ordermap_set_height_Node(struct T_AVL_OrderMap_Node *node);
void _t_AVL_ordermap_balance_Node(T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node);
int _t_AVL_ordermap_get_balanceValue(struct T_AVL_OrderMap_Node *node);
void _t_AVL_ordermap_rotate_right(T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node);
void _t_AVL_ordermap_rotate_left(T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node);

T_AVL_OrderMap t_AVL_ordermap_init(size_t key_typeSize, size_t value_typeSize, T_CompareFunc compareFunc, T_EqualFunc equalFunc)
{
    assert(compareFunc != NULL);
    assert(equalFunc != NULL);
    assert(key_typeSize > 0);
    assert(value_typeSize > 0);

    T_AVL_OrderMap map;
    map.compareFunc = compareFunc;
    map.equalFunc = equalFunc;
    map.head = NULL;
    map.key_typeSize = key_typeSize;
    map.value_typeSize = value_typeSize;
    map.size = 0;
    return map;
}

void t_AVL_ordermap_destroy(T_AVL_OrderMap *map)
{
    assert(map != NULL);
    _t_AVL_ordermap_destroyNode(map->head);
    map->compareFunc = NULL;
    map->equalFunc = NULL;
    map->head = NULL;
    map->key_typeSize = 0;
    map->size = 0;
    map->value_typeSize = 0;
}

int t_AVL_ordermap_insert(T_AVL_OrderMap *map, void *key, void *value)
{
    assert(map != NULL);
    assert(map->compareFunc != NULL);
    assert(map->equalFunc != NULL);
    assert(map->key_typeSize > 0);
    assert(map->value_typeSize > 0);
    assert(key != NULL);
    assert(value != NULL);

    if (_t_AVL_ordermap_findEqualNode(map, map->head, key) != NULL)
    {
        printf("\x1B[31m"
               "The key is already in map\n"
               "\x1B[0m");
        return T_AVL_ORDERMAP_ERROR;
    }
    struct T_AVL_OrderMap_Node *parent = _t_AVL_ordermap_findParentNode(map, map->head, key);
    if (parent == NULL)
    {
        parent = _t_AVL_ordermap_initNode(map, key, value);
        map->head = parent;
    }
    else
    {
        struct T_AVL_OrderMap_Node *node = _t_AVL_ordermap_initNode(map, key, value);
        if (node == NULL)
        {
            printf("\x1B[31m"
                   "Error to create Node\n"
                   "\x1B[0m");
            return T_AVL_ORDERMAP_ERROR;
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

        _t_AVL_ordermap_balance_Node(map, node);
    }

    map->size++;
    return T_AVL_ORDERMAP_SUCCESS;
}

void *t_AVL_ordermap_find(const T_AVL_OrderMap *map, void *key)
{
    assert(map != NULL);
    assert(key != NULL);

    struct T_AVL_OrderMap_Node *targetNode = _t_AVL_ordermap_findEqualNode(map, map->head, key);
    if (targetNode == NULL)
    {
        return NULL;
    }
    return targetNode->data.second;
}

int t_AVL_ordermap_edit(T_AVL_OrderMap *map, void *key, void *value)
{
    assert(map != NULL);
    assert(key != NULL);
    assert(value != NULL);

    struct T_AVL_OrderMap_Node *target = _t_AVL_ordermap_findEqualNode(map, map->head, key);
    if (target == NULL)
    {
        printf("\x1B[31m"
               "The key does not be found in the map\n"
               "\x1B[0m");
        return T_AVL_ORDERMAP_ERROR;
    }
    if (T_pair_setSecond(&target->data, value, map->value_typeSize) == 1)
    {
        return T_AVL_ORDERMAP_ERROR;
    }
    return T_AVL_ORDERMAP_SUCCESS;
}

int t_AVL_ordermap_erase(T_AVL_OrderMap *map, void *key)
{
    assert(map != NULL);
    assert(key != NULL);

    struct T_AVL_OrderMap_Node *target = _t_AVL_ordermap_findEqualNode(map, map->head, key);
    if (target == NULL)
    {
        printf("\x1B[31m"
               "The key does not exist in the map\n"
               "\x1B[0m");
        return T_AVL_ORDERMAP_ERROR;
    }

    if (target->left == NULL && target->right == NULL)
    {
        if (target == map->head)
        {
            map->head = NULL;
        }
        else
        {
            if (target->parent->left == target)
            {
                target->parent->left = NULL;
            }
            else
            {
                target->parent->right = NULL;
            }
            _t_AVL_ordermap_balance_Node(map, target->parent);
        }
        T_pair_destroy(&target->data);
    }
    else if (target->left != NULL && target->right != NULL)
    {
        struct T_AVL_OrderMap_Node *max_left = _t_AVL_ordermap_findMaxNode(map, target->left);
        struct T_AVL_OrderMap_Node *min_right = _t_AVL_ordermap_findMinNode(map, target->right);
        if (map->compareFunc(max_left->data.first, min_right->data.first))
        {
            if (target == map->head)
            {
                map->head = target->left;
            }
            else
            {
                if (target->parent->left == target)
                {
                    target->parent->left = target->left;
                }
                else
                {
                    target->parent->right = target->left;
                }
                _t_AVL_ordermap_balance_Node(map, max_left);
            }

            max_left->right = target->right;
            target->right->parent = max_left;
        }
        else
        {
            if (target == map->head)
            {
                map->head = target->right;
            }
            else
            {
                if (target->parent->left == target)
                {
                    target->parent->left = target->right;
                }
                else
                {
                    target->parent->right = target->right;
                }
                _t_AVL_ordermap_balance_Node(map, min_right);
            }

            min_right->left = target->left;
            target->left->parent = min_right;
        }
        T_pair_destroy(&target->data);
    }
    else
    {
        struct T_AVL_OrderMap_Node *child;
        if (target == map->head)
        {
            map->head = child;
        }
        else
        {
            if (target->left != NULL)
            {
                child = target->left;
            }
            else
            {
                child = target->right;
            }
            if (target->parent->left == target)
            {
                target->parent->left = child;
            }
            else
            {
                target->parent->right = child;
            }
            _t_AVL_ordermap_balance_Node(map, child);
        }

        child->parent = target->parent;
        T_pair_destroy(&target->data);
    }

    map->size--;
    return T_AVL_ORDERMAP_SUCCESS;
}

T_Pair *t_AVL_ordermap_min(const T_AVL_OrderMap *map)
{
    assert(map != NULL);
    if (map->size == 0)
    {
        printf("\x1B[31m"
               "The map is empty.\n"
               "\x1B[0m");
        return NULL;
    }
    return &_t_AVL_ordermap_findMinNode(map, map->head)->data;
}
T_Pair *t_AVL_ordermap_max(const T_AVL_OrderMap *map)
{
    assert(map != NULL);
    if (map->size == 0)
    {
        printf("\x1B[31m"
               "The map is empty.\n"
               "\x1B[0m");
        return NULL;
    }
    return &_t_AVL_ordermap_findMaxNode(map, map->head)->data;
}
const void t_AVL_ordermap_display(const T_AVL_OrderMap *map, T_DisplayFunc displayFunc)
{
    printf("{ ");
    _t_AVL_ordermap_displayNodeMaxToMin(map->head, displayFunc);
    printf("}\n");
}
const void t_AVL_ordermap_displayBreadth(const T_AVL_OrderMap *map, T_DisplayFunc displayFunc)
{
    printf("{ ");
    _t_AVL_ordermap_displayNodeBreadth(map->head, displayFunc);
    printf("}\n");
}
size_t t_AVL_ordermap_get_size(const T_AVL_OrderMap *map)
{
    assert(map != NULL);
    return map->size;
}
size_t t_AVL_ordermap_get_height(const T_AVL_OrderMap *map)
{
    assert(map != NULL);
    return 1 + _t_AVL_ordermap_get_height_Node(map->head);
}

struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findMaxNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node)
{
    if (node->right == NULL)
    {
        return node;
    }
    return _t_AVL_ordermap_findMaxNode(map, node->right);
}
struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findMinNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node)
{
    if (node->left == NULL)
    {
        return node;
    }
    return _t_AVL_ordermap_findMinNode(map, node->left);
}

struct T_AVL_OrderMap_Node *_t_AVL_ordermap_initNode(const T_AVL_OrderMap *map, void *key, void *value)
{
    struct T_AVL_OrderMap_Node *node = malloc(sizeof(struct T_AVL_OrderMap_Node));
    if (node == NULL)
    {
        return NULL;
    }

    node->data = T_pair_init_with(key, map->key_typeSize, value, map->value_typeSize);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 0;
    return node;
}

struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findEqualNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node, void *key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (map->equalFunc(node->data.first, key))
    {
        return node;
    }
    struct T_AVL_OrderMap_Node *foundNode = _t_AVL_ordermap_findEqualNode(map, node->left, key);
    if (foundNode == NULL)
    {
        foundNode = _t_AVL_ordermap_findEqualNode(map, node->right, key);
    }
    return foundNode;
}
struct T_AVL_OrderMap_Node *_t_AVL_ordermap_findParentNode(const T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node, void *key)
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
        return _t_AVL_ordermap_findParentNode(map, node->left, key);
    }
    else
    {
        if (node->right == NULL)
        {
            return node;
        }
        return _t_AVL_ordermap_findParentNode(map, node->right, key);
    }
}

const void _t_AVL_ordermap_displayNodeMaxToMin(struct T_AVL_OrderMap_Node *node, T_DisplayFunc displayFunc)
{
    if (node->left != NULL)
    {
        _t_AVL_ordermap_displayNodeMaxToMin(node->left, displayFunc);
    }
    t_pair_display(&node->data, displayFunc);
    printf(" ");
    if (node->right != NULL)
    {
        _t_AVL_ordermap_displayNodeMaxToMin(node->right, displayFunc);
    }
}

const void _t_AVL_ordermap_displayNodeBreadth(struct T_AVL_OrderMap_Node *node, T_DisplayFunc displayFunc)
{
    T_Queue queue = T_QUEUE_NEW(struct T_AVL_OrderMap_Node);
    t_queue_enqueue(&queue, node);
    struct T_AVL_OrderMap_Node *current;
    while (!t_queue_isEmpty(&queue))
    {
        current = t_queue_front(&queue);
        if (current != NULL)
            t_pair_display(&current->data, displayFunc);
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
        printf("h: %d ", _t_AVL_ordermap_get_height_Node(current));
        t_queue_dequeue(&queue);
    }
    t_queue_destroy(&queue);
}

const void _t_AVL_ordermap_destroyNode(struct T_AVL_OrderMap_Node *node)
{
    if (node->left != NULL)
    {
        _t_AVL_ordermap_destroyNode(node->left);
    }
    if (node->right != NULL)
    {
        _t_AVL_ordermap_destroyNode(node->right);
    }
    T_pair_destroy(&node->data);
    free(node);
}

int _t_AVL_ordermap_get_height_Node(struct T_AVL_OrderMap_Node *node)
{
    if (node == NULL)
    {
        return -1;
    }
    int left_height = _t_AVL_ordermap_get_height_Node(node->left);
    int right_height = _t_AVL_ordermap_get_height_Node(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

void _t_AVL_ordermap_set_height_Node(struct T_AVL_OrderMap_Node *node)
{
    if (node != NULL)
    {
        node->height = _t_AVL_ordermap_get_height_Node(node);
    }
}

void _t_AVL_ordermap_balance_Node(T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node)
{
    if (node == NULL)
    {
        return;
    }
    _t_AVL_ordermap_set_height_Node(node);
    int parent_balanceValue = _t_AVL_ordermap_get_balanceValue(node);

    if (parent_balanceValue == -2)
    {
        int left_child_balanceValue = _t_AVL_ordermap_get_balanceValue(node->left);
        if (left_child_balanceValue == 1)
        {
            // Left-Right Rotation
            _t_AVL_ordermap_rotate_left(map, node->left);
            _t_AVL_ordermap_rotate_right(map, node);
        }
        else
        {
            // Right Rotation
            _t_AVL_ordermap_rotate_right(map, node);
        }
    }
    else if (parent_balanceValue == 2)
    {
        int right_child_balanceValue = _t_AVL_ordermap_get_balanceValue(node->right);

        if (right_child_balanceValue == -1)
        {
            // Right-Left Rotation
            _t_AVL_ordermap_rotate_right(map, node->right);
            _t_AVL_ordermap_rotate_left(map, node);
        }
        else
        {
            // Left Rotation
            _t_AVL_ordermap_rotate_left(map, node);
        }
    }
    _t_AVL_ordermap_balance_Node(map, node->parent);
}

int _t_AVL_ordermap_get_balanceValue(struct T_AVL_OrderMap_Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int left_height = _t_AVL_ordermap_get_height_Node(node->left);
    int right_height = _t_AVL_ordermap_get_height_Node(node->right);
    return right_height - left_height;
}
void _t_AVL_ordermap_rotate_right(T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node)
{
    struct T_AVL_OrderMap_Node *child = node->left;
    if (node->parent != NULL)
    {
        if (node->parent->left == node)
        {
            node->parent->left = child;
        }
        else
        {
            node->parent->right = child;
        }
    }
    else
    {
        map->head = child;
    }
    child->parent = node->parent;
    node->left = child->right;
    if (child->right != NULL)
    {
        child->right->parent = node;
    }
    node->parent = child;
    child->right = node;
    _t_AVL_ordermap_set_height_Node(child);
    _t_AVL_ordermap_set_height_Node(node);
}
void _t_AVL_ordermap_rotate_left(T_AVL_OrderMap *map, struct T_AVL_OrderMap_Node *node)
{
    struct T_AVL_OrderMap_Node *child = node->right;
    if (node->parent != NULL)
    {
        if (node->parent->left == node)
        {
            node->parent->left = child;
        }
        else
        {
            node->parent->right = child;
        }
    }
    else
    {
        map->head = child;
    }
    child->parent = node->parent;
    node->right = child->left;
    if (child->left != NULL)
    {
        child->left->parent = node;
    }
    node->parent = child;
    child->left = node;
    _t_AVL_ordermap_set_height_Node(child);
    _t_AVL_ordermap_set_height_Node(node);
}