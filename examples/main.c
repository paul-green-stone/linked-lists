#include "../include/lists.h"

#include <string.h>
#include <time.h>

/* ================================================================ */

#define RAND(min, max) ((rand() % (max - min + 1)) + min)

/* ================================ */

typedef struct person {

    char* first_name;
    char* last_name;

    unsigned int age;
} Person;

/* ================================ */

/* The list of available first names */
char* first_names[] = {"James", "Mary", "Robert", "Patricia", "John", "Jennifer", "Michael", "Linda", "David", "Elizabeth"};

/* The list of available last names */
char* last_names[] = {"Smith", "Brown", "Tremblay", "Martin", "Roy", "Gagnon", "Lee", "Wilson", "Johnson", "MacDonald"};

/* ================================================================ */

Person* Person_new(void) {

    Person* person = NULL;

    if ((person = calloc(1, sizeof(Person))) == NULL) {
        return NULL;
    }

    person->first_name = strdup(first_names[RAND(0, 9)]);
    person->last_name = strdup(last_names[RAND(0, 9)]);
    person->age = RAND(0, 120);

    /* ======== */

    return person;
}

/* ================================================================ */

void Person_destroy(void* data) {

    Person* person = (Person*) data;

    if (person == NULL) {
        return ;
    }

    free(person->first_name);
    free(person->last_name);

    free(person);

    person = NULL;
}

/* ================================================================ */

void Person_print(void* data, FILE* f) {

    /* Assume data is never NULL, just for the sake of simplicity */
    Person* p = (Person*) data;

    fprintf(f, "%s %s - %u", p->first_name, p->last_name, p->age);
}

/* ================================================================ */

int Person_match(void* data1, void* data2) {

    Person* person1 = (Person*) data1;
    Person* person2 = (Person*) data2;

    return !((strcmp(person1->first_name, person2->first_name) == 0) && (strcmp(person1->last_name, person2->last_name) == 0) && (person1->age == person2->age));
}

/* ================================================================ */

int main(int argc, char** argv) {

    srand(time(0));

    sList_t list = NULL;

    /* Create a new list */
    sList_new(&list, Person_destroy, Person_print, Person_match);

    for (size_t i = 0; i < 10; i++) {
        sList_insert_first(list, Person_new());
    }

    sList_printTo(list, "\n", stdout);

    sNode_t node = NULL;
    void* data = NULL;

    /* Take the third element from the list */
    for (size_t i = 0; i < 3; i++) {
        data = sList_next(list);
    }

    /* Display it */
    printf("\n\nThe third person in the list: ");
    Person_print(data, stdout);

    /* Find the same node the "regular" way */
    sList_find(list, data, &node);
    sNode_data(node, &data);

    /* Display it */
    printf("\n\nWhat we found is (in order to delete): ");
    Person_print(data, stdout);

    /* Delete the found element */
    sList_delete_Node(list, node, &data);
    Person_destroy(data);

    sList_reset(list);
    printf("\n\nPrinting once again:\n----------------\n");
    while ((data = sList_next(list)) != NULL) {
        Person_print(data, stdout);
        printf("\n");
    }

    /* Destroy the list */
    sList_destroy(&list);

    /* ======== */

    return EXIT_SUCCESS;

}

/* ================================================================ */
