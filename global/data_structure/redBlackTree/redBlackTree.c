#include "redBlackTree.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../queue/queue.h"

struct T_RedBlack_Node *_t_redblack_node_init(T_RedBlack_Tree *tree, void *key, void *value, bool isBlack);
void _t_redblack_node_destroy(struct T_RedBlack_Node *node);
struct T_RedBlack_Node *_t_redblack_node_findEqual(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node, void *key);
struct T_RedBlack_Node *_t_redblack_node_findParent(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node, void *key);
struct T_RedBlack_Node *_t_redblack_node_findMin(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
struct T_RedBlack_Node *_t_redblack_node_findMax(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
size_t _t_redblack_get_node_height(struct T_RedBlack_Node *node);
struct T_RedBlack_Node *_t_redblack_getParent(struct T_RedBlack_Node *node);
struct T_RedBlack_Node *_t_redblack_getGrandparent(struct T_RedBlack_Node *node);
struct T_RedBlack_Node *_t_redblack_getUncle(struct T_RedBlack_Node *node);
void _t_redblack_rotate_right(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
void _t_redblack_rotate_left(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
void _t_redblack_removeLeafNode(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
void _t_redblack_removeNodeOnechild(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
void _t_redblack_removeNodeTwochildren(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
void _t_redblack_fixInsert(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
void _t_redblack_fixRemove(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node);
void _t_redblack_displayNodeMaxToMin(struct T_RedBlack_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);
void _t_redblack_displayNodeBreadth(struct T_RedBlack_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2);

T_RedBlack_Tree t_redblack_tree_init(size_t key_typeSize, size_t value_typeSize, T_CompareFunc compareFunc, T_EqualFunc equalFunc)
{
    T_RedBlack_Tree tree;
    tree.head = NULL;
    tree.key_typeSize = key_typeSize;
    tree.value_typeSize = value_typeSize;
    tree.size = 0;
    tree.compareFunc = compareFunc;
    tree.equalFunc = equalFunc;
    return tree;
}

void t_redblack_tree_destroy(T_RedBlack_Tree *tree)
{
    assert(tree != NULL);
    _t_redblack_node_destroy(tree->head);
    tree->compareFunc = NULL;
    tree->equalFunc = NULL;
    tree->head = NULL;
    tree->key_typeSize = 0;
    tree->size = 0;
    tree->value_typeSize = 0;
}

T_Pair *t_redblack_tree_min(const T_RedBlack_Tree *tree)
{
    assert(tree != NULL);
    if (tree->size == 0)
    {
        fprintf(stderr, "Error: The tree is empty.\n");
        return NULL;
    }
    return &_t_redblack_node_findMin(tree, tree->head)->obj;
}

T_Pair *t_redblack_tree_max(const T_RedBlack_Tree *tree)
{
    assert(tree != NULL);
    if (tree->size == 0)
    {
        fprintf(stderr, "Error: The tree is empty.\n");
        return NULL;
    }
    return &_t_redblack_node_findMax(tree, tree->head)->obj;
}

size_t t_redblack_tree_get_size(const T_RedBlack_Tree *tree)
{
    assert(tree != NULL);
    return tree->size;
}

size_t t_redblack_tree_get_height(const T_RedBlack_Tree *tree)
{
    assert(tree != NULL);
    return _t_redblack_get_node_height(tree->head);
}

void *t_redblack_tree_find(const T_RedBlack_Tree *tree, void *key)
{
    assert(tree != NULL);
    assert(key != NULL);
    struct T_RedBlack_Node *targetNode = _t_redblack_node_findEqual(tree, tree->head, key);
    if (targetNode == NULL)
    {
        return NULL;
    }
    return targetNode->obj.second;
}

int t_redblack_tree_insert(T_RedBlack_Tree *tree, void *key, void *value)
{
    assert(tree != NULL);
    assert(key != NULL);
    assert(value != NULL);
    assert(tree->compareFunc != NULL);
    assert(tree->equalFunc != NULL);
    assert(tree->value_typeSize > 0);
    assert(tree->key_typeSize > 0);

    if (tree->head == NULL)
    {
        tree->head = _t_redblack_node_init(tree, key, value, true);
        if (tree->head == NULL)
        {
            fprintf(stderr, "Error: Initialization of the head node failed.\n");
            return 1;
        }
        tree->size++;
        return 0;
    }

    if (_t_redblack_node_findEqual(tree, tree->head, key) != NULL)
    {
        fprintf(stderr, "Error: Duplicate key insertion attempted.\n");
        return 1;
    }
    struct T_RedBlack_Node *parent = _t_redblack_node_findParent(tree, tree->head, key);
    struct T_RedBlack_Node *node = _t_redblack_node_init(tree, key, value, false);
    if (node == NULL)
    {
        fprintf(stderr, "Error: Initialization of the new node failed.\n");
        return 1;
    }
    if (tree->compareFunc(parent->obj.first, key))
    {
        parent->left = node;
        node->parent = parent;
    }
    else
    {
        parent->right = node;
        node->parent = parent;
    }
    tree->size++;
    _t_redblack_fixInsert(tree, node);
    return 0;
}

int t_redblack_edit(T_RedBlack_Tree *tree, void *key, void *value)
{
    assert(tree != NULL);
    assert(key != NULL);
    assert(value != NULL);
    struct T_RedBlack_Node *targetNode = _t_redblack_node_findEqual(tree, tree->head, key);
    if (targetNode == NULL)
    {
        fprintf(stderr, "Error: The key does not be found in the tree.\n");
        return 1;
    }
    if (T_pair_setSecond(&targetNode->obj, value, tree->value_typeSize) == 1)
    {
        return 1;
    }
    return 0;
}

int t_redblack_tree_remove(struct T_RedBlack_Tree *tree, void *key)
{
    assert(tree != NULL);
    assert(key != NULL);

    struct T_RedBlack_Node *targetNode = _t_redblack_node_findEqual(tree, tree->head, key);
    if (targetNode == NULL)
    {
        fprintf(stderr, "Error: The key does not exist in the tree.\n");
        return 1;
    }

    if (targetNode->left == NULL && targetNode->right == NULL)
    {
        _t_redblack_removeLeafNode(tree, targetNode);
    }
    else if (targetNode->left != NULL && targetNode->right != NULL)
    {
        _t_redblack_removeNodeTwochildren(tree, targetNode);
    }
    else
    {
        _t_redblack_removeNodeOnechild(tree, targetNode);
    }

    tree->size--;
    return 0;
}

void t_redblack_display(const T_RedBlack_Tree *tree, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    printf("{ ");
    _t_redblack_displayNodeMaxToMin(tree->head, displayFunc1, displayFunc2);
    printf("}\n");
}
void t_redblack_displayBreadth(const T_RedBlack_Tree *tree, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    printf("{ ");
    _t_redblack_displayNodeBreadth(tree->head, displayFunc1, displayFunc2);
    printf("}\n");
}

struct T_RedBlack_Node *_t_redblack_node_init(T_RedBlack_Tree *tree, void *key, void *value, bool isBlack)
{
    struct T_RedBlack_Node *node = malloc(sizeof(struct T_RedBlack_Node));
    node->obj.first = NULL;
    node->obj.second = NULL;
    if (node == NULL)
    {
        fprintf(stderr, "Error: Memory allocation for node failed.\n");
        return NULL;
    }
    T_pair_setFirst(&node->obj, key, tree->key_typeSize);
    T_pair_setSecond(&node->obj, value, tree->value_typeSize);
    if (node->obj.first == NULL || node->obj.second == NULL)
    {
        fprintf(stderr, "Error: Memory allocation for key or value failed.\n");
        free(node->obj.first);
        free(node->obj.second);
        free(node);
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->isBlack = isBlack;
    return node;
}

void _t_redblack_node_destroy(struct T_RedBlack_Node *node)
{
    if (node->left != NULL)
    {
        _t_redblack_node_destroy(node->left);
    }
    if (node->right != NULL)
    {
        _t_redblack_node_destroy(node->right);
    }
    T_pair_destroy(&node->obj);
    free(node);
}

struct T_RedBlack_Node *_t_redblack_node_findEqual(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node, void *key)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (tree->equalFunc(node->obj.first, key))
    {
        return node;
    }
    struct T_RedBlack_Node *foundNode = _t_redblack_node_findEqual(tree, node->left, key);
    if (foundNode == NULL)
    {
        foundNode = _t_redblack_node_findEqual(tree, node->right, key);
    }
    return foundNode;
}

struct T_RedBlack_Node *_t_redblack_node_findParent(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node, void *key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (tree->compareFunc(node->obj.first, key))
    {
        if (node->left == NULL)
        {
            return node;
        }
        return _t_redblack_node_findParent(tree, node->left, key);
    }
    else
    {
        if (node->right == NULL)
        {
            return node;
        }
        return _t_redblack_node_findParent(tree, node->right, key);
    }
}

struct T_RedBlack_Node *_t_redblack_node_findMin(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    if (node->left == NULL)
    {
        return node;
    }
    return _t_redblack_node_findMin(tree, node->left);
}

struct T_RedBlack_Node *_t_redblack_node_findMax(const T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    if (node->right == NULL)
    {
        return node;
    }
    return _t_redblack_node_findMax(tree, node->right);
}

size_t _t_redblack_get_node_height(struct T_RedBlack_Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    size_t left_height = _t_redblack_get_node_height(node->left);
    size_t right_height = _t_redblack_get_node_height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

struct T_RedBlack_Node *_t_redblack_getParent(struct T_RedBlack_Node *node)
{
    if (node == NULL || node->parent == NULL)
    {
        return NULL;
    }
    return node->parent;
}

struct T_RedBlack_Node *_t_redblack_getGrandparent(struct T_RedBlack_Node *node)
{
    struct T_RedBlack_Node *parent = _t_redblack_getParent(node);
    if (parent == NULL)
    {
        return NULL;
    }
    return _t_redblack_getParent(parent);
}

struct T_RedBlack_Node *_t_redblack_getUncle(struct T_RedBlack_Node *node)
{
    struct T_RedBlack_Node *parent = _t_redblack_getParent(node);
    struct T_RedBlack_Node *grandparent = _t_redblack_getGrandparent(node);
    if (grandparent == NULL)
    {
        return NULL;
    }
    if (parent == grandparent->left)
    {
        return grandparent->right;
    }
    else
    {
        return grandparent->left;
    }
}

void _t_redblack_rotate_right(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    struct T_RedBlack_Node *child = node->left;
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
        tree->head = child;
    }
    child->parent = node->parent;
    node->left = child->right;
    if (child->right != NULL)
    {
        child->right->parent = node;
    }
    node->parent = child;
    child->right = node;
}

void _t_redblack_rotate_left(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    struct T_RedBlack_Node *child = node->right;
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
        tree->head = child;
    }
    child->parent = node->parent;
    node->right = child->left;
    if (child->left != NULL)
    {
        child->left->parent = node;
    }
    node->parent = child;
    child->left = node;
}

void _t_redblack_removeLeafNode(struct T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    _t_redblack_fixRemove(tree, node);
    if (node == tree->head)
    {
        tree->head = NULL;
    }
    else
    {
        if (node->parent->left == node)
        {
            node->parent->left = NULL;
        }
        else
        {
            node->parent->right = NULL;
        }
    }
    T_pair_destroy(&node->obj);
    free(node);
}

void _t_redblack_removeNodeOnechild(struct T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    struct T_RedBlack_Node *child;
    if (node == tree->head)
    {
        tree->head = (node->right != NULL) ? node->right : node->left;
        if (tree->head != NULL)
        {
            tree->head->parent = NULL;
        }
        _t_redblack_fixRemove(tree, tree->head);
    }
    else
    {
        if (node->left != NULL)
        {
            child = node->left;
        }
        else
        {
            child = node->right;
        }
        if (node->parent->left == node)
        {
            node->parent->left = child;
        }
        else
        {
            node->parent->right = child;
        }

        if (child != NULL)
        {
            child->parent = node->parent;
            _t_redblack_fixRemove(tree, child);
        }
    }

    T_pair_destroy(&node->obj);
    free(node);
}

void _t_redblack_removeNodeTwochildren(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    struct T_RedBlack_Node *max_left = _t_redblack_node_findMax(tree, node->left);

    void *temp_first = node->obj.first;
    void *temp_second = node->obj.second;
    node->obj.first = max_left->obj.first;
    node->obj.second = max_left->obj.second;
    max_left->obj.first = temp_first;
    max_left->obj.second = temp_second;

    if (max_left->left != NULL || max_left->right != NULL)
    {
        _t_redblack_removeNodeOnechild(tree, max_left);
    }
    else
    {
        _t_redblack_removeLeafNode(tree, max_left);
    }
}

void _t_redblack_fixInsert(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    struct T_RedBlack_Node *current = node;

    while (current != tree->head && !current->parent->isBlack)
    {
        struct T_RedBlack_Node *parent = _t_redblack_getParent(current);
        struct T_RedBlack_Node *grandparent = _t_redblack_getGrandparent(current);

        if (parent == grandparent->left)
        {
            struct T_RedBlack_Node *uncle = grandparent->right;
            if (uncle != NULL && !uncle->isBlack) // Case 1: Uncle is red
            {
                parent->isBlack = true;
                uncle->isBlack = true;
                grandparent->isBlack = false;
                current = grandparent;
            }
            else
            {
                if (current == parent->right) // Case 2: Node is right child
                {
                    _t_redblack_rotate_left(tree, parent);
                    current = parent;
                    parent = _t_redblack_getParent(current);
                }
                // Case 3: Node is left child
                parent->isBlack = true;
                grandparent->isBlack = false;
                _t_redblack_rotate_right(tree, grandparent);
            }
        }
        else
        {
            struct T_RedBlack_Node *uncle = grandparent->left;
            if (uncle != NULL && !uncle->isBlack) // Case 1: Uncle is red
            {
                parent->isBlack = true;
                uncle->isBlack = true;
                grandparent->isBlack = false;
                current = grandparent;
            }
            else
            {
                if (current == parent->left) // Case 2: Node is left child
                {
                    _t_redblack_rotate_right(tree, parent);
                    current = parent;
                    parent = _t_redblack_getParent(current);
                }
                // Case 3: Node is right child
                parent->isBlack = true;
                grandparent->isBlack = false;
                _t_redblack_rotate_left(tree, grandparent);
            }
        }
    }
    tree->head->isBlack = true;
}

void _t_redblack_fixRemove(T_RedBlack_Tree *tree, struct T_RedBlack_Node *node)
{
    while (node != NULL && node != tree->head && node->isBlack)
    {
        struct T_RedBlack_Node *parent = node->parent;
        struct T_RedBlack_Node *sibling = (node == parent->left) ? parent->right : parent->left;

        if (!sibling)
            return;

        // Case 1: Node's sibling is red

        if (!sibling->isBlack)
        {
            sibling->isBlack = true;
            parent->isBlack = false;
            if (node == parent->left)
            {
                _t_redblack_rotate_left(tree, parent);
            }
            else
            {
                _t_redblack_rotate_right(tree, parent);
            }
            sibling = (node == parent->left) ? parent->right : parent->left;
        }

        if (!sibling)
            return;
        // Case 2: Node's sibling and sibling's children are black
        if ((!sibling->left || sibling->left->isBlack) && (!sibling->right || sibling->right->isBlack))
        {

            sibling->isBlack = false;
            node = parent;
        }
        else
        {

            if (node == parent->left)
            {
                // Case 3: Node's sibling's right child is black
                if (!sibling->right || sibling->right->isBlack)
                {
                    if (sibling->left)
                        sibling->left->isBlack = true;
                    sibling->isBlack = false;
                    _t_redblack_rotate_right(tree, sibling);
                    sibling = parent->right;
                }

                // Case 4: Node's sibling's right child is red
                sibling->isBlack = parent->isBlack;
                parent->isBlack = true;
                if (sibling->right)
                    sibling->right->isBlack = true;
                _t_redblack_rotate_left(tree, parent);
                node = tree->head;
            }
            else
            {

                // Case 3: Node's sibling's left child is black
                if (!sibling->left || sibling->left->isBlack)
                {
                    if (sibling->right)
                        sibling->right->isBlack = true;
                    sibling->isBlack = false;
                    _t_redblack_rotate_left(tree, sibling);
                    sibling = parent->left;
                }

                // Case 4: Node's sibling's left child is red
                sibling->isBlack = parent->isBlack;
                parent->isBlack = true;
                if (sibling->left)
                    sibling->left->isBlack = true;
                _t_redblack_rotate_right(tree, parent);
                node = tree->head;
            }
        }
    }

    if (node)
        node->isBlack = true;
}

void _t_redblack_displayNodeBreadth(struct T_RedBlack_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    if (node == NULL)
    {
        return;
    }

    T_Queue queue = t_queue_init(sizeof(struct T_RedBlack_Node *));
    t_queue_enqueue(&queue, &node);

    while (!t_queue_isEmpty(&queue))
    {
        struct T_RedBlack_Node *current = NULL;
        current = *(struct T_RedBlack_Node **)t_queue_front(&queue);

        if (current != NULL)
        {
            t_pair_display(&current->obj, displayFunc1, displayFunc2);

            if (current->left != NULL)
            {
                t_queue_enqueue(&queue, &current->left);
            }
            if (current->right != NULL)
            {
                t_queue_enqueue(&queue, &current->right);
            }

            printf(" ");
        }
        printf("color: %s, ", current->isBlack ? "black" : "red");
        t_queue_dequeue(&queue);
    }

    t_queue_destroy(&queue);
}

void _t_redblack_displayNodeMaxToMin(struct T_RedBlack_Node *node, T_DisplayFunc displayFunc1, T_DisplayFunc displayFunc2)
{
    if (node->left != NULL)
    {
        _t_redblack_displayNodeMaxToMin(node->left, displayFunc1, displayFunc2);
    }
    t_pair_display(&node->obj, displayFunc1, displayFunc2);
    printf(" ");
    if (node->right != NULL)
    {
        _t_redblack_displayNodeMaxToMin(node->right, displayFunc1, displayFunc2);
    }
}