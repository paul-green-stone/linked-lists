#include <stdio.h>
#include <stdlib.h>
#include "data/LinkedList.h"

/* Initializes a list */
extern void initialize_list(LList* list);

/* Inserts a new node into the tail of the given linear list. Returns 0 on success */
extern int insert_last(LList* list, void* data);

/* Inserts a new node into the head of the given linear list. Returns 0 on success */
extern int insert_first(LList* list, void* data);

/* Deletes the first node from the list */
extern int delete_first(LList* list, void** data);

/* Removes the last element from the list */
extern int delete_last(LList* list, void** data);

/* This function assumes you use a list that contains integer data type */
extern int find_inode(const LList* list, void* data);

/* Makes a copy of a linked list, list, and returns a pointer to it */
extern LList* icopy(const LList* list);