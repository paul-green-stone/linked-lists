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

    errno = 0;

    if (data == NULL) {
        return MISSING_DATA;
    }

    if ((n = calloc(1, sizeof(struct singly_linked_list_node))) == NULL) {
        return errno;
    }

    n->data = data;

    *node = n;

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ========= Node_destroy ========= */
/* ================================ */

static int Node_destroy(sNode_t* node, void** data) {

    if ((node == NULL) || (*node == NULL)) {
        return NULL_NODE;
    }

    *data = (*node)->data;

    free(*node);

    *node = NULL;

    /* ======== */

    return NO_ERROR;
}

/* ================================================================ */
/* =========================== INTERFACE ========================== */
/* ================================================================ */

/* ================================ */
/* =========== sList_new ========== */
/* ================================ */

int sList_new(sList_t* list, void (*destroy)(void* data), void (*print)(void* data, FILE* file), int (*match)(void* data_1, void* data_2)) {

    sList_t l = NULL;

    errno = 0;

    if ((l = calloc(1, sizeof(struct singly_linked_list))) == NULL) {

        /* Out of memory */
        return errno;
    }

    if ((l->methods = calloc(1, sizeof(struct methods))) == NULL) {
        
        /* Out of memory */
        return errno;
    }

    if ((l->data = calloc(1, sizeof(struct data))) == NULL) {
        
        /* Out of memory */
        return errno;
    }

    l->methods->destroy = destroy;
    l->methods->print = print;
    l->methods->match = match;

    *list = l;

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ======== sList_destroy ========= */
/* ================================ */

int sList_destroy(sList_t* list) {

    int code = NO_ERROR;

    void* data = NULL;

    if ((list == NULL) || (*list == NULL)) {
        return NULL_LIST;
    }

    while ((*list)->data->size > 0) {
        
        code = sList_remove_first(*list, &data);

        if ((*list)->methods->destroy != NULL) {
            (*list)->methods->destroy(data);
        }
    }

    free((*list)->data);
    free((*list)->methods);
    free(*list);

    *list = NULL;

    /* ======== */

    return code;
}

/* ================================ */
/* ====== sList_insert_last ======= */
/* ================================ */

int sList_insert_last(const sList_t list, void* data) {

    int code = NO_ERROR;

    sNode_t node = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if ((code = Node_new(data, &node)) != NO_ERROR) {
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

    /* ======== */

    return code;
}

/* ================================ */
/* ===== sList_remove_first ======= */
/* ================================ */

int sList_remove_first(const sList_t list, void** data) {

    int code = NO_ERROR;

    ssize_t size = 0;

    sNode_t node = NULL;

    if (list == NULL) {
        return NULL_LIST;
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

    /* ======== */

    return code;
}

/* ================================ */
/* ========== sList_size ========== */
/* ================================ */

ssize_t sList_size(const sList_t list) {
    
    if (list == NULL) {
        return NULL_LIST;
    }

    /* ======== */

    return list->data->size;
}

/* ================================ */
/* ========= sList_print ========== */
/* ================================ */

int sList_printTo(const sList_t list, const char* delimiter, FILE* file) {

    sNode_t node = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if (list->methods->print == NULL) {
        return MISSING_METHOD;
    }

    for (node = list->data->head; node != NULL; node = node->next) {
        list->methods->print(node->data, file);

        if (node != list->data->tail) {
            fprintf((file == NULL) ? stdout : file, "%s", (delimiter != NULL) ? delimiter : "");
        }
    }

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ====== sList_insert_first ====== */
/* ================================ */

int sList_insert_first(const sList_t list, void* data) {

    int code = NO_ERROR;

    sNode_t node = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if ((code = Node_new(data, &node)) != NO_ERROR) {
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

    /* ======== */

    return code;
}

/* ================================ */
/* ========= sList_clear ========== */
/* ================================ */

int sList_clear(const sList_t list) {

    void* data = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    while (list->data->size > 0) {

        /* The return value can be safely ignored */
        sList_remove_first(list, &data);

        if (list->methods->destroy != NULL) {
            list->methods->destroy(data);
        }
    }

    return NO_ERROR;
}

/* ================================ */
/* ====== sList_remove_last ======= */
/* ================================ */

int sList_remove_last(const sList_t list, void** data) {

    ssize_t size;

    sNode_t node = NULL;
    sNode_t temp = NULL;

    if (list == NULL) {
        return NULL_LIST;
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

    return NO_ERROR;
}

/* ================================ */
/* ========== sList_find ========== */
/* ================================ */

int sList_find(const sList_t list, void* data, sNode_t* node) {

    sNode_t temp = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if (data == NULL) {
        return MISSING_DATA;
    }

    if (list->methods->match == NULL) {
        return MISSING_METHOD;
    }

    for (temp = list->data->head; temp != NULL; temp = temp->next) {

        if (list->methods->match(temp->data, data) == 0) {
            *node = temp;

            return NO_ERROR;
        }
    }

    /* ======== */

    return 1;
}

/* ================================ */
/* ====== sList_insert_after ====== */
/* ================================ */

int sList_insert_after(const sList_t list, const sNode_t node, void* data) {

    int code = NO_ERROR;

    sNode_t new_node = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if ((node == NULL) || (node == list->data->tail)) {
        return sList_insert_last(list, data);
    }

    if (node->list != list) {
        return LIST_MISMATCH;
    }

    if ((code = Node_new(data, &new_node)) != NO_ERROR) {
        return code;
    }

    new_node->next = node->next;
    node->next = new_node;

    list->data->size++;

    new_node->list = list;

    /* ======== */

    return code;
}

/* ================================ */
/* ===== sList_insert_before ====== */
/* ================================ */

int sList_insert_before(const sList_t list, const sNode_t node, void* data) {

    int code = NO_ERROR;

    sNode_t new_node = NULL;
    sNode_t temp = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if ((node == NULL) || (node == list->data->head)) {
        return sList_insert_first(list, data);
    }

    if (node->list != list) {
        return LIST_MISMATCH;
    }

    for (temp = list->data->head; temp->next != node; temp = temp->next) ;

    if ((code = Node_new(data, &new_node)) != NO_ERROR) {
        return code;
    }

    new_node->next = temp->next;
    temp->next = new_node;

    list->data->size++;

    new_node->list = list;

    /* ======== */

    return code;
}

/* ================================ */
/* ====== sList_delete_Node ======= */
/* ================================ */

int sList_delete_Node(const sList_t list, sNode_t node, void** data) {

    sNode_t temp = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if (node == NULL) {
        return NULL_NODE;
    }

    if (node == list->data->head) {
        return sList_remove_first(list, data);
    }

    if (node == list->data->tail) {
        return sList_remove_last(list, data);
    }

    if (node->list != list) {
        return LIST_MISMATCH;
    }

    for (temp = list->data->head; temp->next != node; temp = temp->next) ;

    temp->next = node->next;

    Node_destroy(&node, data);

    list->data->size--;

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ======== sList_foreach ========= */
/* ================================ */

int sList_foreach(const sList_t list, int (*func)(void* data)) {

    int nodes_affected = 0;

    sNode_t node = NULL;

    if (list == NULL) {
        return NULL_LIST;
    }

    if (func == NULL) {
        return MISSING_METHOD;
    }

    for (node = list->data->head; node != NULL; node = node->next) {
        nodes_affected += (func(node->data) == 0) ? 1 : 0;
    }

    /* ======== */

    return nodes_affected;
}

/* ================================ */
/* ========== sList_next ========== */
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
        return NULL_LIST;
    }

    *data = n->data;

    n = n->next;

    if (n == NULL) {
        n = list->data->head;
    }

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ========== sList_head ========== */
/* ================================ */

int sList_head(const sList_t list, sNode_t* node) {

    if (list == NULL) {
        return NULL_LIST;
    }

    *node = list->data->head;

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ========== sList_tail ========== */
/* ================================ */

int sList_tail(const sList_t list, sNode_t* node) {

    if (list == NULL) {
        return NULL_LIST;
    }

    *node = list->data->tail;

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ========== sNode_data ========== */
/* ================================ */

int sNode_data(const sNode_t node, void** data) {

    if (node == NULL) {
        return NULL_NODE;
    }

    *data = node->data;

    /* ======== */

    return NO_ERROR;
}

/* ================================ */
/* ========= sList_perror ========= */
/* ================================ */

void sList_perror(int error_code) {

    struct error {
        int code;
        char* msg;
    } errors[] = {
        {NO_ERROR, "\033[0;32mSuccess\033[0;37m"},
        {NULL_NODE, "\033[0;ERROR\033[0;37m: node as NULL is not expected"},
        {NULL_LIST, "\033[0;ERROR\033[0;37m: list as NULL is not expected"},
        {MISSING_METHOD, "\033[0;33mWARNING\033[0;37m: method/function is missing"},
        {MISSING_DATA, "\033[0;ERROR\033[0;37m: data as NULL is not expected"},
        {LIST_MISMATCH, "033[0;ERROR\033[0;37m: foreign node is encountered"}
    };

    fprintf(stderr, "%s\n", (error_code <= 0) ? errors[-error_code].msg : strerror(error_code));
}

/* ================================================================ */
