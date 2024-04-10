#ifndef singly_list_h
#define singly_list_h

#include "lists.h"

/* ================================================================ */

extern int sList_new(sList_t* list, void (*destroy)(void* data), void (*print)(void* data), int (*match)(void* data_1, void* data_2));

/* ================================ */

extern int sList_destroy(sList_t* list);

/* ================================ */

extern int sList_insert_last(const sList_t list, void* data);

/* ================================ */

extern int sList_remove_first(const sList_t list, void** data);

/* ================================ */

extern ssize_t sList_size(const sList_t list);

/* ================================================================ */

#endif /* singly_list_h */
