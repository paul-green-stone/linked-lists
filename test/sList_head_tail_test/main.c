#include <CUnit/Basic.h>
#include "../../include/lists.h"

#define BUFFER_SIZE 128

/* ================================================================ */
/* ===================== LIST ACTUAL METHODS ====================== */
/* ================================================================ */

void print_int(void* data, FILE* file) {
    fprintf((file == NULL) ? stdout : file, "%d", *((int*) data));
}

/* ================================ */

int match_int(void* data_1, void* data_2) {

    if (data_2 == NULL) {
        return 1;
    }

    return !(*((int*) data_1) == *((int*) data_2));
}

/* ================================ */
/* ====== GLOBAL LINKED LIST ====== */
/* ================================ */

sList_t list = NULL;

/* ================================ */
/* == STATICALLY ALLOCATED ARRAY == */
/* ================================ */

int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

ssize_t size = sizeof(array) / sizeof(array[0]);

/* ================================ */
/* == FILE FOR STORING LIST DATA == */
/* ================================ */

const char* file_name = "what_list_contains.txt";

/* ================================================================ */
/* ==================== sList_insert_last TEST ==================== */
/* ================================================================ */

void sList_insert_last_test(void) {

    sList_new(&list, NULL, print_int, match_int);
    CU_ASSERT_PTR_NOT_NULL(list);

    ssize_t i = 0;

    for (; i < size; i++) {
        sList_insert_last(list, &array[i]);
    }

    CU_ASSERT_EQUAL(sList_size(list), size);
}

/* ================================================================ */
/* ================== sList_head_tail_test TEST =================== */
/* ================================================================ */

void sList_head_tail_test(void) {

    sNode_t head = NULL;
    void* head_data = NULL;

    sNode_t tail = NULL;
    void* tail_data = NULL;

    sList_head(list, &head);
    sList_tail(list, &tail);

    CU_ASSERT_PTR_NOT_NULL(head);
    CU_ASSERT_PTR_NOT_NULL(tail);

    sNode_data(head, &head_data);
    sNode_data(tail, &tail_data);

    CU_ASSERT_EQUAL(*((int*) head_data), 0);
    CU_ASSERT_EQUAL(*((int*) tail_data), 9);
}

/* ================================================================ */

int main(int argc, char** argv) {

    /* List creation and population of it with data */
    CU_pSuite suite1 = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add a suite1 to the registry */
    suite1 = CU_add_suite("sList_insert_last & sList_tail", NULL, NULL);

    if (suite1 == NULL) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* suite1 */
    if ((CU_add_test(suite1, "sList_insert_last", sList_insert_last_test) == NULL) || (CU_add_test(suite1, "sList_head", sList_head_tail_test) == NULL)) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    sList_destroy(&list);

    return CU_get_error();
}

/* ================================================================ */
