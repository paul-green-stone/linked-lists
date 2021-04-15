#include <stdio.h>
#include "interface.h"

void print_list(const LList* list);

int main(int argc, char* argv[])
{
    LList list;
    initialize_list(&list);

    int a = 10;
    int b = 11;
    int c = 12;

    print_list(&list);

    printf("%d\n", find_inode(&list, (void*) &b));

    printf("\n\n\n");

    print_list(icopy(&list));

    return 0;
}

/* ================================================================ */

void print_list(const LList* list)
{
    printf("List size: %zu\n", list->size);
    printf("(");

    if (list->size > 0)
    {
        Node* t = list->head;

        while (t)
        {
            printf("%d", *((int*) t->data));

            if (t->next != NULL)
                printf(", ");

            t = t->next;
        }
    }

    printf(")\n");
}