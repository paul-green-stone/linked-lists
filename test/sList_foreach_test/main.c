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

/* ================================================================ */

int double_odds(void* data) {

    if (*((int*) data) % 2) {
        *((int*) data) = *((int*) data) * 2;
    }
    else {
        return 1;
    }

    return 0;
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
/* ======================= sList_print TEST ======================= */
/* ================================================================ */

void sList_print_test(void) {

    FILE* f = fopen(file_name, "w+");
    /* File size. Number of bytes corresponds to the number of characters in a file (text one) */
    size_t size = 0;

    CU_ASSERT_PTR_NOT_NULL(f);

    /* Expected output */
    char buffer[BUFFER_SIZE] = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9";
    /* What had been read from a file */
    char file_content[BUFFER_SIZE];

    sList_printTo(list, ", ", f);
    
    size = ftell(f);
    fseek(f, 0, SEEK_SET);

    fread(file_content, 1, size, f);

    file_content[size] = '\0';

    CU_ASSERT_STRING_EQUAL(file_content, buffer);

    fclose(f);
}

/* ================================================================ */
/* ====================== sList_foreach TEST ====================== */
/* ================================================================ */

void sList_foreach_test(void) {

    int result = sList_foreach(list, double_odds);

    CU_ASSERT_EQUAL(result, 5);
}

/* ================================================================ */
/* ======================= sList_print TEST ======================= */
/* ================================================================ */

void sList_print_test_suite2(void) {

    FILE* f = fopen(file_name, "w+");
    /* File size. Number of bytes corresponds to the number of characters in a file (text one) */
    size_t size = 0;

    CU_ASSERT_PTR_NOT_NULL(f);

    /* Expected value after clearing and populating once again */
    char buffer[BUFFER_SIZE] = "0, 2, 2, 6, 4, 10, 6, 14, 8, 18";
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
}

/* ================================================================ */

int main(int argc, char** argv) {

    /* List creation and population of it with data */
    CU_pSuite suite1 = NULL;

    /* Clearing and populating */
    CU_pSuite suite2 = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add a suite1 to the registry */
    suite1 = CU_add_suite("sList_insert_last & sList_print", NULL, NULL);

    if (suite1 == NULL) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* Add a suite2 to the registry */
    suite2 = CU_add_suite("sList_foreach & sList_print", NULL, NULL);

    if (suite2 == NULL) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* suite1 */
    if ((CU_add_test(suite1, "sList_insert_last", sList_insert_last_test) == NULL) || (CU_add_test(suite1, "sList_print", sList_print_test) == NULL)) {
        CU_cleanup_registry();

        return CU_get_error();
    }

    /* suite2 */
    if ((CU_add_test(suite2, "sList_foreach", sList_foreach_test) == NULL) || (CU_add_test(suite2, "sList_print", sList_print_test_suite2) == NULL)) {
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
