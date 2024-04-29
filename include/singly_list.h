#ifndef singly_list_h
#define singly_list_h

#include "lists.h"

#define sList_print(list) (sList_printTo(list, stdout))

/* ================================================================ */

extern int sList_new(sList_t* list, void (*destroy)(void* data), void (*print)(void* data, FILE* file), int (*match)(void* data_1, void* data_2));

/* ================================ */

extern int sList_destroy(sList_t* list);

/* ================================ */

extern int sList_insert_last(const sList_t list, void* data);

/* ================================ */

extern int sList_remove_first(const sList_t list, void** data);

/* ================================ */

extern int sList_remove_last(const sList_t list, void** data);

/* ================================ */

extern ssize_t sList_size(const sList_t list);

/* ================================ */

extern int sList_printTo(const sList_t list, const char* delimiter, FILE* file);

/* ================================ */

extern int sList_insert_first(const sList_t list, void* data);

/* ================================ */

extern int sList_clear(const sList_t list);

/* ================================ */

extern int sList_find(const sList_t list, void* data, sNode_t* node);

/* ================================ */

extern int sList_insert_after(const sList_t list, const sNode_t node, void* data);

/* ================================ */

extern int sList_insert_before(const sList_t list, const sNode_t node, void* data);

/* ================================ */

extern int sList_delete_Node(const sList_t list, sNode_t node, void** data);

/* ================================ */

extern int sList_foreach(const sList_t list, int (*func)(void* data));

/* ================================ */

extern int sList_next(const sList_t list, void** data);

/* ================================ */

extern int sList_head(const sList_t list, sNode_t* node);

/* ================================ */

extern int sList_tail(const sList_t list, sNode_t* node);

/* ================================ */

extern int sNode_data(const sNode_t node, void** data);

/* ================================================================ */

#endif /* singly_list_h */
