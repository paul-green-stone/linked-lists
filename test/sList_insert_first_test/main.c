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
/* =================== sList_insert_first TEST ==================== */
/* ================================================================ */

void sList_insert_first_test(void) {

    sList_new(&list, NULL, print_int, NULL);
    CU_ASSERT_PTR_NOT_NULL(list);

    ssize_t i = 0;

    for (; i < size; i++) {
        sList_insert_first(list, &array[i]);
    }

    CU_ASSERT_EQUAL(sList_size(list), size);
}

/* ================================================================ */
/* ======================= sList_print TEST ======================= */
/* ================================================================ */

void test_sList_print(void) {

    FILE* f = fopen(file_name, "w+");
    /* File size. Number of bytes corresponds to the number of characters in a file (text one) */
    size_t size = 0;

    CU_ASSERT_PTR_NOT_NULL(f);

    /* Expected output */
    char buffer[BUFFER_SIZE] = "9, 8, 7, 6, 5, 4, 3, 2, 1, 0";
    /* What had been read from a file */
    char file_content[BUFFER_SIZE];

    sList_printTo(list, ", ", f);
    
    size = ftell(f);
    fseek(f, 0, SEEK_SET);

    fread(file_content, 1, size, f);

    file_content[size] = '\0';

    CU_ASSERT_STRING_EQUAL(file_content, buffer);

    fclose(f);

    remove(file_name);

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
    suite = CU_add_suite("sList_insert_first & test_sList_print", NULL, NULL);

    if (suite == NULL) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* SUITE */
    if ((CU_add_test(suite, "sList_insert_first_test", sList_insert_first_test) == NULL) || (CU_add_test(suite, "sList_print_test", test_sList_print) == NULL)) {
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
