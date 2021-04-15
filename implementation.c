#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

/* Create a new node with the given value. Returns a pointer to Node or NULL */
extern Node* create_node(void* data)
{
    Node* new_node = NULL;

    if ((new_node = (Node*) malloc(sizeof(Node))) != NULL)
    {
        new_node->data = (void*) data;
        new_node->next = NULL;
    }
    else
        fprintf(stdin, "Memory allocation failure\n.");

    return new_node;
}

/* ================================================================ */

extern void initialize_list(LList* list)
{
    list->size = 0;
    list->head = list->tail =  NULL;
}

/* ================================================================ */

extern int insert_last(LList* list, void* data)
{
    Node* new_node = create_node(data);

    /* if (new_node != NULL) */
    if (new_node)
    {
        /* The empty list */
        if (list->size == 0)
            list->head = list->tail = new_node;
        else
        {
            list->tail->next = new_node;
            list->tail = new_node;
        }

        list->size++;
    }
    else
        return 1;

    return 0;
}

/* ================================================================ */

extern int insert_first(LList* list, void* data)
{
    Node* new_node = create_node(data);

    if (new_node)
    {
        /* The empty list */
        if (list->size == 0)
            list->head = list->tail = new_node;
        else
        {
            new_node->next = list->head;
            list->head = new_node;
        }

        list->size++;
    }
    else
        return 1;

    return 0;
}

/* ================================================================ */

int delete_first(LList* list, void** data)
{
    Node* deleted;

    /* If the given list is not empty */
    if (list->size > 0)
    {
        deleted = list->head;
        *data = deleted->data;

        if (list->size == 1)
            list->head = list->tail = NULL;
        else
            list->head = list->head->next;

        free(deleted);
        list->size--;
    }
    else
        return 1; // node has not been deleted from the list

    return 0; // node has been deleted from the list
}

/* ================================================================ */

int delete_last(LList* list, void** data)
{
    Node* current;
    Node* previous;

    if (list->size > 0)
    {
        *data = list->tail->data;

        if (list->size == 1)
        {
            free(list->tail);
            list->head = list->tail = NULL;
        }
        else
        {
            for (previous = list->head, current = list->head->next; current != list->tail; previous = current, current = current->next) ;

            previous->next = NULL;
            list->tail = previous;
            free(current);
        }

        list->size--;
    }
    else
        return 1; // node has not been deleted from the list

    return 0; // node has been deleted from the list
}

/* ================================================================ */

extern int find_inode(const LList* list, void* data)
{
    Node* t;
    size_t i = 1;

    if (list)
    {
        if (list->size > 0)
        {
            for (t = list->head; t != NULL; t = t->next, i++ )
            {
                if ((int*) t->data == (int*) data)
                    return i;
            }
        }
    }

    return -1; // a node with the given value doesn't exist
}

/* ================================================================ */

extern LList* icopy(const LList* list)
{
    LList* new_list = (LList*) malloc(sizeof(LList));
    Node* t;

    if (list)
    {
        initialize_list(new_list);

        for (t = list->head; t != NULL; t = t->next)
            insert_last(new_list, t->data);
    }

    return new_list;
}