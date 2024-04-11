#include <CUnit/Basic.h>
#include "../include/lists.h"

#define BUFFER_SIZE 128

/* ================================================================ */
/* ===================== LIST ACTUAL METHODS ====================== */
/* ================================================================ */

void print_int(void* data, FILE* file) {
    fprintf((file == NULL) ? stdout : file, "%d", *((int*) data));
}

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

/* ================================ */
/* == FILE FOR STORING LIST DATA == */
/* ================================ */

const char* file_name = "what_list_contains.txt";

/* ================================================================ */
/* ======================== sList_new TEST ======================== */
/* ================================================================ */

void test_sList_new(void) {

    sList_new(&list, NULL, print_int, NULL);

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

/* ================================================================ */
/* ======================= sList_print TEST ======================= */
/* ================================================================ */

void test_sList_print(void) {

    /* Reopen STDOUT */
    FILE* f = fopen(file_name, "w+");
    /* File size. Number of bytes corresponds to the number of characters in a file (text one) */
    size_t size = 0;

    CU_ASSERT_PTR_NOT_NULL(f);

    /* Expected output of the function */
    char buffer[BUFFER_SIZE] = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9";
    /* What had been read from a file */
    char file_content[BUFFER_SIZE];

    sList_printTo(list, ", ", f);
    
    size = ftell(f);
    fseek(f, 0, SEEK_SET);

    fread(file_content, 1, size, f);

    CU_ASSERT_STRING_EQUAL(file_content, buffer);

    fclose(f);
}

/* ================================ */
/* ================================ */
/* ================================ */

int main(int argc, char** argv) {

    /* List creation and population of it with data */
    CU_pSuite suite = NULL;

    /* Examination of the list */
    CU_pSuite suite1 = NULL;

    /* Destroying the list */
    CU_pSuite suite2 = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add a suite to the registry */
    suite = CU_add_suite("List creation and population of it with data", NULL, NULL);
    suite1 = CU_add_suite("Examination of the list", NULL, NULL);
    suite2 = CU_add_suite("Destroying the list", NULL, NULL);

    if (suite == NULL) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* SUITE */
    if ((CU_add_test(suite, "test_sList_new & test_sList_insert_last", test_sList_new) == NULL) || (CU_add_test(suite, "test_sList_insert_last", test_sList_insert_last) == NULL)) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* SUITE 1 */
    if ((CU_add_test(suite1, "test_sList_print", test_sList_print) == NULL)) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* SUITE 2 */
    if ((CU_add_test(suite2, "test_sList_destroy", test_sList_destroy) == NULL)) {
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
