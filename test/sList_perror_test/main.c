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

/* ================================================================ */
/* ==================== sList_insert_last TEST ==================== */
/* ================================================================ */

void sList_insert_last_test(void) {

    sList_new(&list, NULL, NULL, match_int);
    CU_ASSERT_PTR_NOT_NULL(list);

    ssize_t i = 0;

    for (; i < size; i++) {
        sList_insert_last(list, &array[i]);
    }

    (sList_size(list), size);
}

/* ================================================================ */
/* ====================== sList_perror TEST ======================= */
/* ================================================================ */

void sList_perror_test(void) {

    int code = sList_print(list);
    CU_ASSERT_EQUAL(code, MISSING_METHOD);

    /* ================ */

    int wrond_data = 99;
    sNode_t node = NULL;

    code = sList_find(list, &wrond_data, &node);
    CU_ASSERT_EQUAL(code, 1);

    /* ================ */

    void* null_data = NULL;

    code = sList_find(list, null_data, &node);
    CU_ASSERT_EQUAL(code, MISSING_DATA);

    /* ================ */

    code = sList_insert_first(NULL, &wrond_data);
    CU_ASSERT_EQUAL(code, NULL_LIST);

    /* ================ */

    code = sList_delete_Node(list, NULL, &null_data);
    CU_ASSERT_EQUAL(code, NULL_NODE);

    /* ================ */

    sList_t l = NULL;
    node = NULL;

    void* data = NULL;

    sList_new(&l, NULL, NULL, NULL);
    CU_ASSERT_PTR_NOT_NULL(l);

    sList_find(list, (array + 0), &node);
    CU_ASSERT_PTR_NOT_NULL(node);

    code = sList_delete_Node(l, node, &data);
    CU_ASSERT_EQUAL(code, LIST_MISMATCH);

    fprintf(stderr, "%s\n", sList_error(code));

    sList_destroy(&l);
}

/* ================================================================ */

int main(int argc, char** argv) {

    /* List creation and population of it with data */
    CU_pSuite suite1 = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add a suite1 to the registry */
    suite1 = CU_add_suite("sList_insert_last & sList_perror", NULL, NULL);

    if (suite1 == NULL) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* suite1 */
    if ((CU_add_test(suite1, "sList_insert_last_test", sList_insert_last_test) == NULL) || (CU_add_test(suite1, "sList_perror_test", sList_perror_test) == NULL)) {
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
