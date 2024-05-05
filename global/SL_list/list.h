#ifndef tin_SL_List
#define tin_SL_List
#include <stddef.h>

#define T_SL_LIST_ERROR 1
#define T_SL_LIST_SUCCESS 0

struct T_SL_Node
{
    void *data;
    struct T_SL_Node *next;
};

typedef struct
{
    struct T_SL_Node *first;
    struct T_SL_Node *end;
    size_t size;
    size_t typeSize;
} T_SL_List;

// Constructor
T_SL_List t_SL_list_init(int typeSize);
T_SL_List t_SL_list_clone(const T_SL_List *list);
int t_SL_list_insertAtEnd(T_SL_List *list, void *element);
int t_SL_list_insertAtBegin(T_SL_List *list, void *element);
int t_SL_list_insertAt(T_SL_List *list, void *element, size_t index);
int t_SL_list_deleteAtEnd(T_SL_List *list);
int t_SL_list_deleteAtBegin(T_SL_List *list);
int t_SL_list_deleteAt(T_SL_List *list, size_t index);
void *t_SL_list_getBegin(const T_SL_List *list);
void *t_SL_list_getEnd(const T_SL_List *list);
void *t_SL_list_getAt(const T_SL_List *list, size_t index);
int t_SL_list_clear(T_SL_List *list);
int t_SL_list_destroy(T_SL_List *list);

struct T_SL_Node *_t_SL_list_nodeInit(size_t typeSize);
struct T_SL_Node *_t_SL_list_nodeBegin(const T_SL_List *list);
struct T_SL_Node *_t_SL_list_nodeEnd(const T_SL_List *list);
struct T_SL_Node *_t_SL_list_nodeAt(const T_SL_List *list, size_t index);

#define T_SL_LIST_NEW(type) t_SL_list_init(sizeof(type))
#define T_SL_LIST_GET_BEGIN_AS(type, list) *(type *)t_SL_list_getBegin(&list)
#define T_SL_LIST_GET_END_AS(type, list) *(type *)t_SL_list_getEnd(&list)
#define T_SL_LIST_GET_AT_AS(type, list, index) *(type *)t_SL_list_getAt(&list, index)
#define T_SL_LIST_NODE_VALUE_AS(type, node) *(type *)node->data
#endif
