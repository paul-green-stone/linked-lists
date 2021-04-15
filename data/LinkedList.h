#ifndef _LinkedList_
#define _LinkedList_

#include <stdlib.h>

typedef struct _node
{
    void* data; // type unsafety
    struct _node* next;
} Node;

typedef struct _linear_list
{
    size_t size;
    struct _node* head;
    struct _node* tail;
} LList;

#endif