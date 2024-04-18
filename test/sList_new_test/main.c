#include <CUnit/Basic.h>
#include "../../include/lists.h"

#define BUFFER_SIZE 128

/* ================================================================ */

/* ================================ */
/* ====== GLOBAL LINKED LIST ====== */
/* ================================ */

sList_t list = NULL;

/* ================================================================ */
/* ======================== sList_new TEST ======================== */
/* ================================================================ */

void sList_new_test(void) {

    sList_new(&list, NULL, NULL, NULL);

    CU_ASSERT_PTR_NOT_NULL(list);
}

/* ================================================================ */
/* ====================== sList_destroy TEST ====================== */
/* ================================================================ */

void sList_destroy_test(void) {

    sList_destroy(&list);

    CU_ASSERT_PTR_NULL(list);
}

/* ================================================================ */
/* ====================== sList_destroy TEST ====================== */
/* ================================================================ */

void test_sList_destroy(void) {

    sList_destroy(&list);

    CU_ASSERT_PTR_NULL(list);
}

/* ================================================================ */

int main(int argc, char** argv) {

    /* List creation and population of it with data */
    CU_pSuite suite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add a suite to the registry */
    suite = CU_add_suite("sList_new & sList_destroy", NULL, NULL);

    if (suite == NULL) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* SUITE */
    if ((CU_add_test(suite, "sList_new_test", sList_new_test) == NULL) || (CU_add_test(suite, "test_sList_destroy", test_sList_destroy) == NULL)) {
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
