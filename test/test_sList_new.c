#include <CUnit/Basic.h>
#include "../include/lists.h"

/* ================================================================ */

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
/* ======================== sList_new TEST ======================== */
/* ================================================================ */

void test_sList_new(void) {

    sList_new(&list, NULL, NULL, NULL);

    CU_ASSERT_PTR_NOT_NULL(list);
}

/* ================================================================ */
/* ====================== sList_destroy TEST ====================== */
/* ================================================================ */

void test_sList_destroy(void) {

    sList_destroy(&list);

    CU_ASSERT_PTR_NULL(list);
}

/* ================================================================ */
/* ==================== sList_insert_last TEST ==================== */
/* ================================================================ */

void test_sList_insert_last(void) {

    ssize_t i = 0;

    for (; i < size; i++) {
        sList_insert_last(list, &array[i]);
    }

    CU_ASSERT_EQUAL(sList_size(list), size);
}

/* ================================ */
/* ================================ */
/* ================================ */

int main(int argc, char** argv) {

    CU_pSuite suite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add a suite to the registry
    suite = CU_add_suite("sList_new & sList_destroy", NULL, NULL);

    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test function to the suite
    if (
        (CU_add_test(suite, "test_sList_new", test_sList_new) == NULL)
        ||
        (CU_add_test(suite, "test_sList_insert_last", test_sList_insert_last) == NULL)
        ||
        (CU_add_test(suite, "test_sList_destroy", test_sList_destroy) == NULL)
        ) {

            CU_cleanup_registry();
            return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

/* ================================================================ */
