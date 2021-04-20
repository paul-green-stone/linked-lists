#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

/*
    (RU)
    Вспомогательная функция для автоматизации создания узлов.

*   Функция принимает указатель на любой тип данных, что делает код более уязвимым (type safety).

    Возвращает указатель на Node (Node*) в случае успеха, и NULL в случае ошибки.

    ================================================================

    (EN)
    An auxiliary function for automatic nodes creation.

    The function receives a pointer to any data type (void*), which makes it less stable.

    The function returns a pointer to Node (Node*) on success, NULL on error.

*/
Node* create_node(void* data)
{
    Node* new_node = NULL;

    if ((new_node = (Node*) calloc(1, sizeof(Node))) != NULL)
    {
        new_node->data = (void*) data;
        new_node->next = NULL;
    }
    else
        fprintf(stdin, "Memory allocation failure\n.");

    return new_node;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

LList* create_list(void)
{
    LList* new_list = NULL;

    if ((new_list = (LList*) calloc(1, sizeof(LList))) != NULL)
    {
        new_list->size = 0;
        new_list->head = new_list->tail = NULL;
    }

    return new_list;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

int initialize_list(LList** list)
{
    int result = 0;

    if (!*(list))
    {
        if ((*(list) = (LList*) calloc(1, sizeof(LList))) == NULL)
            result = 1;
        else
        {
            (*list)->size = 0;
            (*list)->head = (*list)->tail = NULL;
        }
    }
    else if (((*list)->size > 0) && ((*list)->head) && ((*list)->tail))
    {
        fprintf(stdout, "List is not empty. The List initialization may cause data loss and memory leak.\n");
        result = 1;
    }
    else
    {
        (*list)->size = 0;
        (*list)->head = (*list)->tail = NULL;
    }

    return result;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

extern int insert_last(LList** list, void* data)
{
    int result = 0;
    Node* new_node = create_node(data);

    if ((*list) && new_node)
    {
        if ((*list)->size == 0)
            (*list)->head = (*list)->tail = new_node;
        else
        {
            (*list)->tail->next = new_node;
            (*list)->tail = new_node;
        }

        ++(*list)->size;
    }
    else
        result = 1;

    return result;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

extern int insert_first(LList** list, void* data)
{
    int result = 0;
    Node* new_node = create_node(data);

    if ((*list) && new_node)
    {
        if ((*list)->size == 0)
            (*list)->head = (*list)->tail = new_node;
        else
        {
            new_node->next = (*list)->head;
            (*list)->head = new_node;
        }

        ++(*list)->size;
    }
    else
        result = 1;

    return 1;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

int delete_first(LList** list, void** data)
{
    int result = 0;
    Node* d_node = NULL;

    if ((*list) && (*list)->size > 0)
    {
        d_node = (*list)->head;
        *data = d_node->data;

        if ((*list)->size == 1)
            (*list)->head = (*list)->tail = NULL;
        else
            (*list)->head = (*list)->head->next;

        free(d_node);
        --(*list)->size;
    }
    else
        result = 1;

    return result;
}

/* ================================================================ */

int delete_last(LList** list, void** data)
{
    int result = 0;

    Node* previous, *current, *d_node;
    previous = current = d_node = NULL;

    if ((*list) && (*list)->size > 0)
    {
        d_node = (*list)->tail;
        *data = d_node->data;

        if ((*list)->size == 1)
            (*list)->head = (*list)->tail = NULL;
        else
        {
            previous = (*list)->head;
            current = (*list)->head->next;

            while (current->next) previous = current, current = current->next;

            (*list)->tail = previous;
            (*list)->tail = NULL;

            free(d_node);
        }

        --(*list)->size;
    }
    else
        result = 1;

    return result;
}