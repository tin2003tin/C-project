#ifndef tin_CSL_List
#define tin_CSL_List
#include <stddef.h>

#define T_CSL_LIST_ERROR 1
#define T_CSL_LIST_SUCCESS 0

struct T_CSL_Node
{
    void *data;
    struct T_CSL_Node *next;
};

typedef struct
{
    struct T_CSL_Node *first;
    struct T_CSL_Node *end;
    size_t size;
    size_t typeSize;
} T_CSL_List;

// Constructor
T_CSL_List t_CSL_list_init(int typeSize);
int t_CSL_list_insertAtEnd(T_CSL_List *list, void *element);
int t_CSL_list_insertAtBegin(T_CSL_List *list, void *element);
int t_CSL_list_insertAt(T_CSL_List *list, void *element, size_t index);
int t_CSL_list_deleteAtEnd(T_CSL_List *list);
int t_CSL_list_deleteAtBegin(T_CSL_List *list);
int t_CSL_list_deleteAt(T_CSL_List *list, size_t index);
void *t_CSL_list_getBegin(T_CSL_List *list);
void *t_CSL_list_getEnd(T_CSL_List *list);
void *t_CSL_list_getAt(T_CSL_List *list, size_t index);
int t_CSL_list_clear(T_CSL_List *list);
int t_CSL_list_destroy(T_CSL_List *list);

struct T_CSL_Node *_t_CSL_list_nodeInit(size_t typeSize);
struct T_CSL_Node *_t_CSL_list_nodeBegin(T_CSL_List *list);
struct T_CSL_Node *_t_CSL_list_nodeEnd(T_CSL_List *list);
struct T_CSL_Node *_t_CSL_list_nodeAt(T_CSL_List *list, size_t index);

#define T_CSL_LIST_NEW(type) t_CSL_list_init(sizeof(type))
#define T_CSL_LIST_GET_BEGIN_AS(type, list) *(type *)t_CSL_list_getBegin(&list)
#define T_CSL_LIST_GET_END_AS(type, list) *(type *)t_CSL_list_getEnd(&list)
#define T_CSL_LIST_GET_AT_AS(type, list, index) *(type *)t_CSL_list_getAt(&list, index)
#define T_CSL_LIST_NODE_VALUE_AS(type, node) *(type *)node->data
#endif
