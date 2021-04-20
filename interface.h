#include <stdio.h>
#include <stdlib.h>
#include "data/LinkedList.h"

/*
    (RU)
    Создает линейный список.

    Возвращает указатель на список (LList*) в случае успеха, NULL в случае ошибки.

    ================================================================

    (EN)
    Creates a linked list.

    The function returns a pointer to a linked list (LList*) on success and NULL on error.
*/
extern LList* create_list(void);

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/*
    (RU)
    Инициализирует список list.

    Эта функция должна быть вызвана перед вызовами любых других функций для работы со списком list.
    
    Возвращает 0 в случае успеха, 1 в случае ошибки.

    ================================================================

    (EN)
    Initializes the given list [list].

    The function must be called before any other functions which operate on list [list].

    The function returns 0 on success and 1 on error.
*/
extern int initialize_list(LList** list);

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/*
    (RU)
    Вставляет новый узел со значение data в конец списка list.

    Возвращает 0 в случае успеха, 1 в случае ошибки.

    ================================================================

    (EN)
    Inserts a new node with the given value [data] at the tail of the linked list [list].

    The function returns 0 on success and 1 on error.
*/
extern int insert_last(LList** list, void* data);

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/*
    (RU)
    Вставляет новый узел со знчение data в начало списка list.

    Возвращает 0 в случае успеха, 1 в случае ошибки.

    ================================================================

    (EN)
    Inserts a new node with the given value [data] at the head of the linked list [list].

    The function returns 0 on success and 1 on error.
*/
extern int insert_first(LList** list, void* data);

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/*
    (RU)
    Удаляет первый узел из списка list и сохраняет его значение в data.

    Возвращает 0 в случае успеха, 1 в случае ошибки.

    ================================================================

    (EN)
    Removes a node from the head of the list [list] and stores its data in the [data] variable.

    The function returns 0 on success and 1 on error.
*/
extern int delete_first(LList** list, void** data);

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/*
    (RU)
    Удаляет последний узел из списка list и сохраняет его значение в data.

    Возвращает 0 в случае успеха, 1 в случае ошибки.

    ================================================================

    (EN)
    Removes a node from the tail of the list [list] and stores its data in the [data] variable.

    The function returns 0 on success and 1 on error.
*/
extern int delete_last(LList** list, void** data);