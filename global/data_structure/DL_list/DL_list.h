#ifndef tin_DL_List
#define tin_DL_List
#include <stddef.h>

#define T_DL_LIST_ERROR 1
#define T_DL_LIST_SUCCUESS 0

struct T_DL_Node
{
    void *data;
    struct T_DL_Node *next;
    struct T_DL_Node *previous;
};

typedef struct
{
    struct T_DL_Node *first;
    struct T_DL_Node *end;
    size_t size;
    size_t typeSize;
} T_DL_List;

T_DL_List t_DL_list_init(size_t typeSize);
T_DL_List t_DL_list_clone(const T_DL_List *list);
int t_DL_list_insertAtEnd(T_DL_List *list, void *element);
int t_DL_list_insertAtBegin(T_DL_List *list, void *element);
int t_DL_list_insertAt(T_DL_List *list, void *element, size_t index);
int t_DL_list_deleteAtEnd(T_DL_List *list);
int t_DL_list_deleteAtBegin(T_DL_List *list);
int t_DL_list_deleteAt(T_DL_List *list, size_t index);
void *t_DL_list_getBegin(const T_DL_List *list);
void *t_DL_list_getEnd(const T_DL_List *list);
void *t_DL_list_getAt(const T_DL_List *list, size_t index);
int t_DL_list_clear(T_DL_List *list);
int t_DL_list_destroy(T_DL_List *list);

struct T_DL_Node *_t_DL_list_nodeInit(size_t typeSize);
struct T_DL_Node *_t_DL_list_nodeBegin(const T_DL_List *list);
struct T_DL_Node *_t_DL_list_nodeEnd(const T_DL_List *list);
struct T_DL_Node *_t_DL_list_nodeAt(const T_DL_List *list, size_t index);

#define T_DL_LIST_NEW(type) t_DL_list_init(sizeof(type))
#define T_DL_LIST_GET_BEGIN_AS(type, list) *(type *)t_DL_list_getBegin(&list)
#define T_DL_LIST_GET_END_AS(type, list) *(type *)t_DL_list_getEnd(&list)
#define T_DL_LIST_GET_AT_AS(type, list, index) *(type *)t_DL_list_getAt(&list, index)
#define T_DL_LIST_NODE_VALUE_AS(type, node) *(type *)node->data
#endif
