#include "../include/lists.h"

/* ================================================================ */

struct singly_linked_list {

    Data data;
    Methods methods;
};

/* ================================ */

struct singly_linked_list_node {

    sNode_t next;

    void* data;

    sList_t list;
};

/* ================================ */

struct methods {

    void (*destroy)(void* data);

    void (*print)(void* data, FILE* stream);

    int (*match)(void* data_1, void* data_2);
};

/* ================================ */

struct data {
    ssize_t size;

    sNode_t head;
    sNode_t tail;
};

/* ================================================================ */
/* ============================ STATIC ============================ */
/* ================================================================ */

/* ================================ */
/* =========== Node_new =========== */
/* ================================ */

static int Node_new(void* data, sNode_t* node) {

    sNode_t n = NULL;

    if (data == NULL) {
        return 1;
    }

    if ((n = calloc(1, sizeof(struct singly_linked_list_node))) == NULL) {
        return 12;
    }

    n->data = data;

    *node = n;

    return 0;
}

/* ================================ */
/* ========= Node_destroy ========= */
/* ================================ */

static int Node_destroy(sNode_t* node, void** data) {

    if ((node == NULL) || (*node == NULL)) {
        return 1;
    }

    *data = (*node)->data;

    free(*node);

    *node = NULL;

    return 0;
}

/* ================================================================ */
/* =========================== INTERFACE ========================== */
/* ================================================================ */

/* ================================ */
/* =========== sList_new ========== */
/* ================================ */

int sList_new(sList_t* list, void (*destroy)(void* data), void (*print)(void* data, FILE* file), int (*match)(void* data_1, void* data_2)) {

    sList_t l = NULL;

    if ((l = calloc(1, sizeof(struct singly_linked_list))) == NULL) {

        /* Out of memory */
        return 12;
    }

    if ((l->methods = calloc(1, sizeof(struct methods))) == NULL) {
        
        /* Out of memory */
        return 12;
    }

    if ((l->data = calloc(1, sizeof(struct data))) == NULL) {
        
        /* Out of memory */
        return 12;
    }

    l->methods->destroy = destroy;
    l->methods->print = print;
    l->methods->match = match;

    *list = l;

    return 0;
}

/* ================================ */
/* ======== sList_destroy ========= */
/* ================================ */

int sList_destroy(sList_t* list) {

    int result = 0;
    void* data = NULL;

    if ((list == NULL) || (*list == NULL)) {
        return -1;
    }

    while ((*list)->data->size > 0) {
        
        result = sList_remove_first(*list, &data);

        if ((*list)->methods->destroy != NULL) {
            (*list)->methods->destroy(data);
        }
    }

    free((*list)->data);
    free((*list)->methods);
    free(*list);

    *list = NULL;

    return result;
}

/* ================================ */
/* ====== sList_insert_last ======= */
/* ================================ */

int sList_insert_last(const sList_t list, void* data) {

    int code = 0;
    sNode_t node = NULL;

    if (list == NULL) {
        return 1;
    }

    if ((code = Node_new(data, &node)) != 0) {
        return code;
    }

    if (list->data->size == 0) {
        list->data->head = list->data->tail = node;
    }
    else {
        list->data->tail->next = node;
        list->data->tail = node;
    }

    list->data->size++;

    node->list = list;

    return code;
}

/* ================================ */
/* ===== sList_remove_first ======= */
/* ================================ */

int sList_remove_first(const sList_t list, void** data) {

    int code = 0;

    ssize_t size = 0;

    sNode_t node = NULL;

    if (list == NULL) {
        return 1;
    }

    size = list->data->size;

    if (size > 0) {

        *data = list->data->head->data;
        node = list->data->head;

        if (size == 1) {
            list->data->head = list->data->tail = NULL;
        }
        else {
            list->data->head = list->data->head->next;
        }

        code = Node_destroy(&node, data);

        list->data->size--;
    }

    return code;
}

/* ================================ */
/* ========== sList_size ========== */
/* ================================ */

ssize_t sList_size(const sList_t list) {
    
    if (list == NULL) {
        return -1;
    }

    return list->data->size;
}

/* ================================ */
/* ========= sList_print ========== */
/* ================================ */

int sList_printTo(const sList_t list, const char* delimiter, FILE* file) {

    sNode_t node = NULL;

    if (list == NULL) {
        return 1;
    }

    if (list->methods->print == NULL) {
        return 1;
    }

    for (node = list->data->head; node != NULL; node = node->next) {
        list->methods->print(node->data, file);

        if (node != list->data->tail) {
            fprintf((file == NULL) ? stdout : file, "%s", (delimiter != NULL) ? delimiter : "");
        }
    }

    return 0;
}

/* ================================ */
/* ====== sList_insert_first ====== */
/* ================================ */

int sList_insert_first(const sList_t list, void* data) {

    int code = 0;
    sNode_t node = NULL;

    if (list == NULL) {
        return -1;
    }

    if ((code = Node_new(data, &node)) != 0) {
        return code;
    }

    if (list->data->size == 0) {
        list->data->head = list->data->tail = node;
    }
    else {
        node->next = list->data->head;
        list->data->head = node;
    }

    list->data->size++;

    node->list = list;

    return code;
}

/* ================================ */
/* ====== sList_insert_clear ====== */
/* ================================ */

int sList_clear(const sList_t list) {

    void* data = NULL;

    if (list == NULL) {
        return 1;
    }

    while (list->data->size > 0) {

        /* The return value can be safely ignored */
        sList_remove_first(list, &data);

        if (list->methods->destroy != NULL) {
            list->methods->destroy(data);
        }
    }

    return 0;
}

/* ================================================================ */
