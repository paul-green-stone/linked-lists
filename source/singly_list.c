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

/* ================================ */
/* ====== sList_remove_last ======= */
/* ================================ */

int sList_remove_last(const sList_t list, void** data) {

    ssize_t size;

    sNode_t node = NULL;
    sNode_t temp = NULL;

    if (list == NULL) {
        return 1;
    }

    size = list->data->size;

    if (size > 0) {

        node = list->data->tail;
        *data = node->data;

        if (size == 1) {
            list->data->head = list->data->tail = NULL;
        }
        else {

            for (temp = list->data->head; temp->next != list->data->tail; temp = temp->next) ;

            list->data->tail = temp;
            list->data->tail->next = NULL;
        }

        Node_destroy(&node, data);

        list->data->size--;
    }

    /* ======== */

    return 0;
}

/* ================================ */
/* ========== sList_find ========== */
/* ================================ */

int sList_find(const sList_t list, void* data, sNode_t* node) {

    sNode_t temp = NULL;

    if (list == NULL) {
        return 1;
    }

    if (data == NULL) {
        return 1;
    }

    if (list->methods->match == NULL) {
        return 1;
    }

    for (temp = list->data->head; temp != NULL; temp = temp->next) {

        if (list->methods->match(temp->data, data) == 0) {
            *node = temp;

            return 0;
        }
    }

    /* ======== */

    return 1;
}

/* ================================ */
/* ====== sList_insert_after ====== */
/* ================================ */

int sList_insert_after(const sList_t list, const sNode_t node, void* data) {

    sNode_t new_node = NULL;

    if (list == NULL) {
        return 1;
    }

    if ((node == NULL) || (node == list->data->tail)) {
        return sList_insert_last(list, data);
    }

    if (node->list != list) {
        return 1;
    }

    if (Node_new(data, &new_node) != 0) {
        return 1;
    }

    new_node->next = node->next;
    node->next = new_node;

    list->data->size++;

    new_node->list = list;

    /* ======== */

    return 0;
}

/* ================================ */
/* ===== sList_insert_before ====== */
/* ================================ */

int sList_insert_before(const sList_t list, const sNode_t node, void* data) {

    sNode_t new_node = NULL;
    sNode_t temp = NULL;

    if (list == NULL) {
        return 1;
    }

    if ((node == NULL) || (node == list->data->head)) {
        return sList_insert_first(list, data);
    }

    if (node->list != list) {
        return 1;
    }

    for (temp = list->data->head; temp->next != node; temp = temp->next) ;

    if (Node_new(data, &new_node) != 0) {
        return 1;
    }

    new_node->next = temp->next;
    temp->next = new_node;

    list->data->size++;

    new_node->list = list;

    /* ======== */

    return 0;
}

/* ================================ */
/* ====== sList_delete_Node ======= */
/* ================================ */

int sList_delete_Node(const sList_t list, sNode_t node, void** data) {

    sNode_t temp = NULL;

    if (list == NULL) {
        return 1;
    }

    if (node == list->data->head) {
        return sList_remove_first(list, data);
    }

    if (node == list->data->tail) {
        return sList_remove_last(list, data);
    }

    if (node->list != list) {
        return 1;
    }

    for (temp = list->data->head; temp->next != node; temp = temp->next) ;

    temp->next = node->next;

    Node_destroy(&node, data);

    list->data->size--;

    /* ======== */

    return 0;
}

/* ================================ */
/* ======== sList_foreach ========= */
/* ================================ */

int sList_foreach(const sList_t list, int (*func)(void* data)) {

    int nodes_affected = 0;

    sNode_t node = NULL;

    if (list == NULL) {
        return -1;
    }

    if (func == NULL) {
        return -1;
    }

    for (node = list->data->head; node != NULL; node = node->next) {
        nodes_affected += (func(node->data) == 0) ? 1 : 0;
    }

    /* ======== */

    return nodes_affected;
}

/* ================================ */
/* ========= sList_next =========== */
/* ================================ */

int sList_next(const sList_t list, void** data) {

    /* List that is being operated on */
    static sList_t l = NULL;

    /* The list node whose data was returned by the previous call */
    static sNode_t n = NULL;

    // The first time the function is being called requires us to set up its internals
    // or
    // when the new list specified does not match the one specified in the iterator.
    if ((l == NULL) || ((l != list) && (list != NULL))) {

        l = list;

        if (list->data->size > 0) {
            n = list->data->head;
        }
    }

    if (l == NULL) {
        return 1;
    }

    *data = n->data;

    n = n->next;

    if (n == NULL) {
        n = list->data->head;
    }

    /* ======== */

    return 0;
}

/* ================================ */
/* ========= sList_head =========== */
/* ================================ */

int sList_head(const sList_t list, sNode_t* node) {

    if (list == NULL) {
        return 1;
    }

    *node = list->data->head;

    /* ======== */

    return 0;
}

/* ================================ */
/* ========= sList_tail =========== */
/* ================================ */

int sList_tail(const sList_t list, sNode_t* node) {

    if (list == NULL) {
        return 1;
    }

    *node = list->data->tail;

    /* ======== */

    return 0;
}

/* ================================ */
/* ========= sNode_data =========== */
/* ================================ */

int sNode_data(const sNode_t node, void** data) {

    if (node == NULL) {
        return 1;
    }

    *data = node->data;

    /* ======== */

    return 0;
}

/* ================================================================ */
